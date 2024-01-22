#include <future>
#include <memory>

#include "mandelbrot/mandelbrot.hpp"
#include "mandelbrot/openmp.hpp"
#include "mandelbrot/sequential.hpp"
#include "ui/menu.hpp"
#include "ui/state.hpp"
#include "ui/window.hpp"
#include "utility/stopwatch.hpp"

int main() {
  using mandelbrot_visualizer::Mandelbrot;
  using mandelbrot_visualizer::OpenMPMandelbrot;
  using mandelbrot_visualizer::SequentialMandelbrot;
  using mandelbrot_visualizer::Stopwatch;
  using mandelbrot_visualizer::ui::Menu;
  using mandelbrot_visualizer::ui::MenuState;
  using mandelbrot_visualizer::ui::Mode;
  using mandelbrot_visualizer::ui::Window;
  using std::make_unique;

  const auto start_width = 1200;
  const auto start_height = 900;
  Window window("Mandelbrot Visualizer", start_width, start_height);

  std::unique_ptr<Mandelbrot> mandelbrot = nullptr;

  MenuState current_state = {Mode::kSequential, {}, {}, 0};
  MenuState last_state = current_state;

  const auto menu = [&]() { current_state.mode = Menu::ShowMenu(last_state); };

  // FIXME: replace with stack with mutex ... or something
  std::vector<std::future<std::unique_ptr<Mandelbrot>>> results{};
  const auto render_mandelbrot = [&](int display_w, int display_h) {
    current_state.display_width = display_w;
    current_state.display_height = display_h;

    if (current_state.NeedsRecomputation(last_state)) {
      current_state.is_computing = true;

      const auto compute = [&]() -> std::unique_ptr<Mandelbrot> {
        auto next = [&]() -> std::unique_ptr<Mandelbrot> {
          switch (current_state.mode) {
            case Mode::kSequential:
              return make_unique<SequentialMandelbrot>(display_h, display_w);
            case Mode::kOpenMP:
              return make_unique<OpenMPMandelbrot>(display_h, display_w);
            default:
              assert(false);
          }
        }();

        current_state.compute_time =
            Stopwatch::Time([&]() { next->Compute(); });
        using namespace std::chrono_literals;
        return next;
      };

      results.emplace_back(std::async(std::launch::async, compute));
    }

    if (!results.empty()) {
      auto& result = results.back();
      if (result.valid()) {
        using namespace std::chrono_literals;
        switch (std::future_status status = result.wait_for(1ms); status) {
          case std::future_status::deferred:
          case std::future_status::timeout:
            break;
          case std::future_status::ready:
            mandelbrot = result.get();
            results.clear();
            current_state.is_computing = false;
            break;
        }
      }
    }

    current_state.draw_time = Stopwatch::Time([&]() {
      if (!current_state.is_computing && mandelbrot != nullptr)
        mandelbrot->Draw();
    });

    last_state = current_state;
  };

  window.EndlessRender(menu, render_mandelbrot);

  return 0;
}
