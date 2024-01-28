#include "../src/mandelbrot/mandelbrot.hpp"

#include <benchmark/benchmark.h>

#include "../src/mandelbrot/openmp.hpp"
#include "../src/mandelbrot/sequential.hpp"

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,misc-use-anonymous-namespace)
static volatile float dummy = 0;

// NOLINTNEXTLINE(readability-identifier-naming,misc-use-anonymous-namespace)
static void BM_MANDELBROT(
    benchmark::State &state,
    std::unique_ptr<mandelbrot_visualizer::Mandelbrot> mandel) {
  std::optional<mandelbrot_visualizer::MandelbrotData> tmp = std::nullopt;
  for ([[maybe_unused]] auto _ : state) {
    tmp = std::move(mandel->Compute(false));
  }

  dummy = tmp.value().pixels[0].r;
}

auto KSettings() {
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  return mandelbrot_visualizer::Settings{
      .height = 1000,
      .width = 1000,
      .max_iterations = 1000,
      .progress = nullptr,
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
