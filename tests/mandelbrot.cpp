#include <gtest/gtest.h>

#include "../src/mandelbrot/openmp.hpp"
#include "../src/mandelbrot/sequential.hpp"

namespace mandelbrot_visualizer::tests {
auto TestSettings() {
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  return mandelbrot_visualizer::Settings{
      .height = 1000,
      .width = 1000,
      .max_iterations = 1000,
      .progress = nullptr,
      .area = {.start = {-2.0F, -1.0F}, .end = {1.0F, 1.0F}}};
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
}
};  // namespace mandelbrot_visualizer::tests

// NOLINTNEXTLINE(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
TEST(Oracle, OpenMP) {
  using mandelbrot_visualizer::OpenMPMandelbrot;
  using mandelbrot_visualizer::SequentialMandelbrot;

  const auto reference =
      SequentialMandelbrot(mandelbrot_visualizer::tests::TestSettings())
          .Compute(false);
  EXPECT_TRUE(reference.has_value());

  const auto open_mp =
      OpenMPMandelbrot(mandelbrot_visualizer::tests::TestSettings())
          .Compute(false);
  EXPECT_TRUE(open_mp.has_value());

  // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
  EXPECT_EQ(*reference, *open_mp);
}
