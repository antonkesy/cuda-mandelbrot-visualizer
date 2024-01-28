#include "../src/mandelbrot/mandelbrot.hpp"

#include <benchmark/benchmark.h>

#include "../src/mandelbrot/openmp.hpp"
#include "../src/mandelbrot/sequential.hpp"

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
// static volatile int dummy = 0;

// NOLINTNEXTLINE(readability-identifier-naming,misc-use-anonymous-namespace)
static void BM_MANDELBROT(
    benchmark::State &state,
    std::unique_ptr<mandelbrot_visualizer::Mandelbrot> mandel) {
  for ([[maybe_unused]] auto _ : state) {
    mandel->Compute(false);
  }

  // TODO(ak): compute should return list of pixels to avoid optimization
  // dummy = A[0];
}

auto KSettings() {
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  return mandelbrot_visualizer::Settings{
      .height = 900,
      .width = 900,
      .max_iterations = 1000,
      .progress = std::make_shared<float>(0),
      .area = {.start = {-2.0F, -1.0F}, .end = {1.0F, 1.0F}}};
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
}

// NOLINTBEGIN(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory,misc-use-anonymous-namespace)
BENCHMARK_CAPTURE(
    BM_MANDELBROT, sequential,
    std::make_unique<mandelbrot_visualizer::SequentialMandelbrot>(KSettings()));
BENCHMARK_CAPTURE(
    BM_MANDELBROT, sequential,
    std::make_unique<mandelbrot_visualizer::OpenMPMandelbrot>(KSettings()));
// NOLINTEND(cert-err58-cpp,cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory,misc-use-anonymous-namespace)

BENCHMARK_MAIN();  // NOLINT
