#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <complex>
#include <vector>

namespace mandelbrot_visualizer {

class Mandelbrot {
 public:
  Mandelbrot(const int height, const int width)
      : height(height), width(width), pixels(height * width) {}
  virtual ~Mandelbrot() = default;
  Mandelbrot(const Mandelbrot &) = default;
  Mandelbrot(Mandelbrot &&) = default;
  Mandelbrot &operator=(const Mandelbrot &) = delete;
  Mandelbrot &operator=(Mandelbrot &&) = delete;

  // not best desing -> can be forgotten to call ...
  virtual void Compute() = 0;
  virtual void Draw() = 0;

  [[nodiscard]] std::complex<double> PixelToComplex(int x, int y) const;

  [[nodiscard]] static ImVec4 MandelbrotColor(const std::complex<double> &c);

 protected:
  // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
  const int height;
  const int width;
  std::vector<ImVec4> pixels;
  // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
};

}  // namespace mandelbrot_visualizer
