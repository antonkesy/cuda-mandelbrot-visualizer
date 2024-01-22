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
    ++iterations;
  }

  const auto hue = (static_cast<float>(iterations) / max_iterations);
  ui::RGBColor rgb{};
  ImGui::ColorConvertHSVtoRGB(hue, 1, iterations < max_iterations ? 0 : 1,
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
