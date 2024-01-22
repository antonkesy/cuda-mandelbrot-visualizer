#pragma once

#include <iostream>

#include "mandelbrot.hpp"

namespace mandelbrot_visualizer {

class OpenMPMandelbrot : public Mandelbrot {
 public:
  explicit OpenMPMandelbrot(const Settings &settings) : Mandelbrot(settings) {
    // TODO(ak): print to UI
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    char *has_cancel = getenv("OMP_CANCELLATION");
    if (has_cancel == nullptr) {
      std::cerr << "OpenMPMandelbrot: OMP_CANCELLATION not set\n";
    }
  }

  void Compute(const std::atomic<bool> &request_stop) override {
    *progress = 0;
#pragma omp parallel shared(pixels, request_stop) default(none)
#pragma omp for schedule(dynamic)
    for (int y = 0; y < height; ++y) {
      *progress = static_cast<float>(y) / static_cast<float>(height);
      if (request_stop) {
#pragma omp cancel for
      }
      for (int x = 0; x < width; ++x) {
        std::complex<double> c = PixelToComplex(x, y);
        pixels[y * width + x] = MandelbrotColor(c);
      }
    }

    *progress = 1;
  }

  void Draw() override {
    glRasterPos2i(-1, -1);
    glDrawPixels(width, height, GL_RGBA, GL_FLOAT, pixels.data());
  }
};

}  // namespace mandelbrot_visualizer
