#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <atomic>
#include <complex>
#include <vector>

#include "../ui/state.hpp"

namespace mandelbrot_visualizer {

class Mandelbrot {
 public:
  Mandelbrot(const int height, const int width, const ui::RGBColor &base_color)
      : height(height),
        width(width),
        pixels(height * width),
        base_color(base_color) {}
  virtual ~Mandelbrot() = default;
  Mandelbrot(const Mandelbrot &) = default;
  Mandelbrot(Mandelbrot &&) = default;
  Mandelbrot &operator=(const Mandelbrot &) = delete;
  Mandelbrot &operator=(Mandelbrot &&) = delete;

  // TODO(ak): make this a parameter
  static constexpr int kMaxIterations = 1000;

  // not best desing -> can be forgotten to call ...
  virtual void Compute(const std::atomic<bool> &request_stop) = 0;
  virtual void Draw() = 0;

  [[nodiscard]] std::complex<double> PixelToComplex(int x, int y) const;

  [[nodiscard]] ImVec4 MandelbrotColor(const std::complex<double> &c) const;

  [[nodiscard]] static int Iteration(const std::complex<double> &c);

 protected:
  // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
  ui::RGBColor base_color{};
  const int height;
  const int width;
  std::vector<ImVec4> pixels;
  // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
};

}  // namespace mandelbrot_visualizer
