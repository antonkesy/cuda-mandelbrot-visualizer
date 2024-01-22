#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <atomic>
#include <complex>
#include <memory>
#include <vector>

#include "../ui/state.hpp"

namespace mandelbrot_visualizer {

class Mandelbrot {
 public:
  struct Settings {
    int height;
    int width;
    ui::RGBColor base_color;
    int max_iterations;
    std::shared_ptr<float> progress;
  };

  explicit Mandelbrot(const Settings &settings)
      : height(settings.height),
        width(settings.width),
        pixels(height * width),
        base_color(settings.base_color),
        max_iterations(settings.max_iterations),
        progress(settings.progress) {}
  virtual ~Mandelbrot() = default;
  Mandelbrot(const Mandelbrot &) = default;
  Mandelbrot(Mandelbrot &&) = default;
  Mandelbrot &operator=(const Mandelbrot &) = delete;
  Mandelbrot &operator=(Mandelbrot &&) = delete;

  // not best desing -> can be forgotten to call ...
  virtual void Compute(const std::atomic<bool> &request_stop) = 0;
  virtual void Draw() = 0;

  [[nodiscard]] std::complex<double> PixelToComplex(int x, int y) const;

  [[nodiscard]] ImVec4 MandelbrotColor(const std::complex<double> &c) const;

  [[nodiscard]] int Iteration(const std::complex<double> &c) const;

 protected:
  // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
  ui::RGBColor base_color{};
  const int height;
  const int width;
  std::vector<ImVec4> pixels;
  const int max_iterations;
  std::shared_ptr<float> progress;
  // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
};

}  // namespace mandelbrot_visualizer
