#include <memory>

#include "mandelbrot/mandelbrot.hpp"
#include "mandelbrot/sequential.hpp"
#include "ui/menu.hpp"
#include "ui/window.hpp"

int main() {
  using mandelbrot_visualizer::Mandelbrot;
  using mandelbrot_visualizer::SequentialMandelbrot;
  using mandelbrot_visualizer::ui::Menu;
  using mandelbrot_visualizer::ui::Mode;
  using mandelbrot_visualizer::ui::Window;
  using std::make_unique;

  const auto start_width = 1200;
  const auto start_height = 900;
  Window window("Cuda Mandelbrot Visualizer", start_width, start_height);

  bool use_cuda = false;

  auto last_width = 0;
  auto last_height = 0;
  auto last_mode = Mode::kSequential;

  std::unique_ptr<Mandelbrot> mandelbrot =
      std::make_unique<SequentialMandelbrot>(0, 0);

  auto mode = Mode::kSequential;

  const auto menu = [&]() { mode = Menu::ShowMenu(); };
  const auto render_mandelbrot = [&](int display_w, int display_h) {
    if (last_width != display_w || last_height != display_h ||
        last_mode != mode) {
      // TODO(ak): calculate in background -> dont block UI
      last_width = display_w;
      last_height = display_h;
      last_mode = mode;

      switch (mode) {
        case Mode::kSequential:
          mandelbrot = make_unique<SequentialMandelbrot>(display_h, display_w);
          break;
        case Mode::kParallel:
          // mandelbrot = make_unique<ParallelMandelbrot>(display_h, display_w);
          // mandelbrot = make_unique<SequentialMandelbrot>(display_h,
          // display_w);
          break;
      }
      mandelbrot->Compute();
    }

    mandelbrot->Draw();
  };

  window.EndlessRender(menu, render_mandelbrot);

  return 0;
}
