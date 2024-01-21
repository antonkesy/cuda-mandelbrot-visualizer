#include <chrono>
#include <memory>

#include "mandelbrot/mandelbrot.hpp"
#include "mandelbrot/openmp.hpp"
#include "mandelbrot/sequential.hpp"
#include "ui/menu.hpp"
#include "ui/state.hpp"
#include "ui/window.hpp"

int main() {
  using mandelbrot_visualizer::Mandelbrot;
  using mandelbrot_visualizer::OpenMPMandelbrot;
  using mandelbrot_visualizer::SequentialMandelbrot;
  using mandelbrot_visualizer::ui::Menu;
  using mandelbrot_visualizer::ui::MenuState;
  using mandelbrot_visualizer::ui::Mode;
  using mandelbrot_visualizer::ui::Window;
  using std::make_unique;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  const auto start_width = 1200;
  const auto start_height = 900;
  Window window("Cuda Mandelbrot Visualizer", start_width, start_height);

  std::unique_ptr<Mandelbrot> mandelbrot =
      std::make_unique<SequentialMandelbrot>(0, 0);

  MenuState current_state = {Mode::kSequential, {}, {}, 0};
  MenuState last_state = current_state;

  const auto menu = [&]() { current_state.mode = Menu::ShowMenu(last_state); };
  const auto render_mandelbrot = [&](int display_w, int display_h) {
    current_state.display_width = display_w;
    current_state.display_height = display_h;

    if (last_state != current_state) {
      // TODO(ak): calculate in background -> dont block UI

      switch (current_state.mode) {
        case Mode::kSequential:
          mandelbrot = make_unique<SequentialMandelbrot>(display_h, display_w);
          break;
        case Mode::kOpenMP:
          mandelbrot = make_unique<OpenMPMandelbrot>(display_h, display_w);
          break;
      }
      auto start = high_resolution_clock::now();
      mandelbrot->Compute();
      auto stop = high_resolution_clock::now();
      current_state.compute_time = duration_cast<milliseconds>(stop - start);
    }

    auto start = high_resolution_clock::now();
    mandelbrot->Draw();
    auto stop = high_resolution_clock::now();
    current_state.draw_time = duration_cast<milliseconds>(stop - start);

    last_state = current_state;
  };

  window.EndlessRender(menu, render_mandelbrot);

  return 0;
}
