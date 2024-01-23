#pragma once

#include "mandelbrot.hpp"

namespace mandelbrot_visualizer {

class SequentialMandelbrot : public Mandelbrot {
 public:
  explicit SequentialMandelbrot(const Settings& settings)
      : Mandelbrot(settings) {}

  void Compute(const std::atomic<bool>& request_stop) override {
    *progress = 0;
    for (int y = 0; y < height; ++y) {
      *progress = static_cast<float>(y) / static_cast<float>(height);
      for (int x = 0; x < width; ++x) {
        if (request_stop) return;
        std::complex<double> c = PixelToComplex(x, y, width, height, area);
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
