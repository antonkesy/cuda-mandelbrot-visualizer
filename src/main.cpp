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
  using mandelbrot_visualizer::ui::Mode;
  using mandelbrot_visualizer::ui::VisualizerState;
  using mandelbrot_visualizer::ui::Window;
  using mandelbrot_visualizer::ui::WindowInfo;
  using std::make_unique;

  const auto start_size = 900;
  Window window("Mandelbrot Visualizer", start_size, start_size);

  std::unique_ptr<Mandelbrot> mandelbrot = nullptr;

  VisualizerState current_state;
  VisualizerState last_state = current_state;

  const auto menu = [&]() { Menu::ShowMenu(current_state); };

  std::atomic<bool> request_stop{false};
  // FIXME: replace with stack with mutex ... or something
  std::vector<std::future<std::unique_ptr<Mandelbrot>>> results{};

  const auto render_mandelbrot = [&](const WindowInfo& window) {
    current_state.display_width = window.width;
    current_state.display_height = window.height;

    if (current_state.NeedsRecomputation(last_state) ||
        (mandelbrot == nullptr && results.empty())) {
      mandelbrot = nullptr;
      request_stop = true;

      const auto compute = [&]() -> std::unique_ptr<Mandelbrot> {
        Mandelbrot::Settings settings{window.height, window.width,
                                      current_state.base_color,
                                      current_state.max_iterations};
        auto next = [&]() -> std::unique_ptr<Mandelbrot> {
          switch (current_state.mode) {
            case Mode::kSequential:
              return make_unique<SequentialMandelbrot>(settings);
            case Mode::kOpenMP:
              return make_unique<OpenMPMandelbrot>(settings);
            default:
              assert(false);
          }
        }();

        request_stop = false;
        current_state.is_computing = true;
        current_state.compute_time =
            Stopwatch::Time([&]() { next->Compute(request_stop); });
        current_state.is_computing = false;
        return next;
      };

      results.emplace_back(std::async(std::launch::async, compute));
    }

    request_stop = results.size() > 1;

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
            // invalidate computation if there are more futures available
            if (results.size() > 1) mandelbrot = nullptr;
            results.clear();
            break;
        }
      }
    }

    current_state.draw_time = Stopwatch::Time([&]() {
      if (mandelbrot != nullptr) mandelbrot->Draw();
    });

    last_state = current_state;
  };

  window.EndlessRender(menu, render_mandelbrot);

  return 0;
}
