#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <atomic>
#include <complex>
#include <memory>
#include <vector>

#include "settings.hpp"

namespace mandelbrot_visualizer {

class Mandelbrot {
 public:
  explicit Mandelbrot(const Settings &settings)
      : height(settings.height),
        width(settings.width),
        pixels(height * width),
        max_iterations(settings.max_iterations),
        progress(settings.progress),
        area(settings.area) {}
  virtual ~Mandelbrot() = default;
  Mandelbrot(const Mandelbrot &) = default;
  Mandelbrot(Mandelbrot &&) = default;
  Mandelbrot &operator=(const Mandelbrot &) = delete;
  Mandelbrot &operator=(Mandelbrot &&) = delete;

  // not best desing -> can be forgotten to call ...
  virtual void Compute(const std::atomic<bool> &request_stop) = 0;
  virtual void Draw() = 0;

  [[nodiscard]] static std::complex<double> PixelToComplex(int x, int y,
                                                           int width,
                                                           int height,
                                                           Settings::Area area);

  [[nodiscard]] ImVec4 MandelbrotColor(const std::complex<double> &c) const;

  [[nodiscard]] int Iteration(const std::complex<double> &c) const;

 protected:
  // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
  const int height;
  const int width;
  std::vector<ImVec4> pixels;
  const int max_iterations;
  const std::shared_ptr<float> progress;
  const Settings::Area area;
  // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes,cppcoreguidelines-avoid-const-or-ref-data-members)
};

}  // namespace mandelbrot_visualizer
