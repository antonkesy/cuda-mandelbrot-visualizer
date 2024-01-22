#include "mandelbrot.hpp"

namespace mandelbrot_visualizer {

std::complex<double> Mandelbrot::PixelToComplex(int x, int y) const {
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  double real = (x - width / 2.0) * 4.0 / width;
  double imag = (y - height / 2.0) * 4.0 / height;
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
  return {real, imag};
}

ImVec4 Mandelbrot::MandelbrotColor(const std::complex<double> &c) const {
  std::complex<double> z = 0;
  int iterations = 0;
  const int max_iterations = 1000;

  while (std::abs(z) <= 2 && iterations < max_iterations) {
    z = z * z + c;
    iterations++;
  }

  float hue = static_cast<float>(iterations) / max_iterations;
  return ImVec4(hue, base_color[0], base_color[1], base_color[2]);
}

}  // namespace mandelbrot_visualizer
