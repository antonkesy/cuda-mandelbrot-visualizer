#pragma once

#include <iostream>

#include "mandelbrot.hpp"

namespace mandelbrot_visualizer {

class OpenMPMandelbrot : public Mandelbrot {
 public:
  OpenMPMandelbrot(const int height, const int width, ui::RGBColor base_color)
      : Mandelbrot(height, width, base_color) {
    // TODO(ak): print to UI
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    char *has_cancel = getenv("OMP_CANCELLATION");
    if (has_cancel == nullptr) {
      std::cerr << "OpenMPMandelbrot: OMP_CANCELLATION not set\n";
    }
  }

  void Compute(const std::atomic<bool> &request_stop) override {
#pragma omp parallel shared(pixels, request_stop) default(none)
#pragma omp for schedule(dynamic)
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        if (request_stop) {
#pragma omp cancel for
        }
        std::complex<double> c = PixelToComplex(x, y);
        pixels[y * width + x] = MandelbrotColor(c);
      }
    }
  }

  void Draw() override {
    glRasterPos2i(-1, -1);
    glDrawPixels(width, height, GL_RGBA, GL_FLOAT, pixels.data());
  }
};

}  // namespace mandelbrot_visualizer
