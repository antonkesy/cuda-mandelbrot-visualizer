#pragma once

#include "mandelbrot.hpp"

namespace mandelbrot_visualizer {

class SequentialMandelbrot : public Mandelbrot {
 public:
  SequentialMandelbrot(const int height, const int width)
      : Mandelbrot(height, width) {}

  void Compute() override {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
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
