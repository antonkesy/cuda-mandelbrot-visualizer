#include "mandelbrot.hpp"

#include <array>

namespace mandelbrot_visualizer {

std::complex<double> Mandelbrot::PixelToComplex(int x, int y, int width,
                                                int height,
                                                Settings::Area area) {
  const double c_real =
      static_cast<double>(x) / width * (area.end.real() - area.start.real()) +
      area.start.real();
  const double c_img = (static_cast<double>(height) - y) / height *
                           (area.start.imag() - area.end.imag()) +
                       area.end.imag();

  return {c_real, c_img};
}

int Mandelbrot::Iteration(const std::complex<double> &c) const {
  std::complex<double> z = 0;
  int n = 0;
  while (std::abs(z) <= 2 && n < max_iterations) {
    z *= z;
    z += c;
    ++n;
  }
  if (n == max_iterations) return max_iterations;
  return n - static_cast<int>(std::log(std::log2(std::abs(z))));
}

ImVec4 Mandelbrot::MandelbrotColor(const std::complex<double> &c) const {
  // TODO(ak): add more color schemes
  //  https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set

  const auto iterations = Mandelbrot::Iteration(c);
  const auto hue =
      (static_cast<float>(iterations) / static_cast<float>(max_iterations));
  std::array<float, 3> rgb{0, 0, 0};
  ImGui::ColorConvertHSVtoRGB(hue, 1, iterations < max_iterations ? 1 : 0,
                              rgb[0], rgb[1], rgb[2]);

  return {rgb[0], rgb[1], rgb[2], 1.0F};
}

}  // namespace mandelbrot_visualizer
