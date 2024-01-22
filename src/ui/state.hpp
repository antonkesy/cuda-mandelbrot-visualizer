#pragma once

#include <array>
#include <chrono>

#include "mode.hpp"
namespace mandelbrot_visualizer::ui {

using std::chrono::milliseconds;

using RGBColor = std::array<float, 3>;

struct VisualizerState {
  Mode mode = Mode::kSequential;
  milliseconds compute_time{};
  milliseconds draw_time{};
  int display_width{};
  int display_height{};
  bool is_computing{};
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  RGBColor base_color{21, 116, 211};  // blue
  int max_iterations{625};
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

  [[nodiscard]] bool NeedsRecomputation(const VisualizerState& other) const {
    return mode != other.mode || display_width != other.display_width ||
           display_height != other.display_height ||
           base_color != other.base_color ||
           max_iterations != other.max_iterations;
  }
};

}  // namespace mandelbrot_visualizer::ui
