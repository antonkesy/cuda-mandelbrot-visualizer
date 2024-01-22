#include "mandelbrot.hpp"

namespace mandelbrot_visualizer {

std::complex<double> Mandelbrot::PixelToComplex(int x, int y) const {
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  double real = (x - width / 2.0) * 4.0 / width;
  double imag = (y - height / 2.0) * 4.0 / height;
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
  return {real, imag};
}

int Mandelbrot::Iteration(const std::complex<double> &c) {
  std::complex<double> z = 0;
  int n = 0;
  while (std::abs(z) <= 2 && n < Mandelbrot::kMaxIterations) {
    z *= z;
    z += c;
    ++n;
  }
  if (n == Mandelbrot::kMaxIterations) return Mandelbrot::kMaxIterations;
  return n - static_cast<int>(std::log(std::log2(std::abs(z))));
}

ImVec4 Mandelbrot::MandelbrotColor(const std::complex<double> &c) const {
  const auto iterations = Mandelbrot::Iteration(c);
  const auto hue =
      (static_cast<float>(iterations) / Mandelbrot::kMaxIterations);
  ui::RGBColor rgb{};
  ImGui::ColorConvertHSVtoRGB(hue, 1,
                              iterations < Mandelbrot::kMaxIterations ? 0 : 1,
                              rgb[0], rgb[1], rgb[2]);

  (void)base_color;
  // FIXME: enable base color again
  //  const auto add_base_color = [](float color, float hue) {
  //    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  //    return std::clamp(0.0F, (color / 255), 1.0F);
  //    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
  //  };
  return {rgb[0], rgb[1], rgb[2], 1.0F};
}

}  // namespace mandelbrot_visualizer
