#pragma once

#include <array>
#include <chrono>

#include "mode.hpp"
namespace mandelbrot_visualizer::ui {

using std::chrono::milliseconds;

using RGBColor = std::array<float, 3>;

struct MenuState {
  Mode mode = Mode::kSequential;
  milliseconds compute_time{};
  milliseconds draw_time{};
  int display_width{};
  int display_height{};
  bool is_computing{};
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
  RGBColor base_color{21, 116, 211};  // blue

  [[nodiscard]] bool NeedsRecomputation(const MenuState& other) const {
    return mode != other.mode || display_width != other.display_width ||
           display_height != other.display_height ||
           base_color != other.base_color;
  }
};

}  // namespace mandelbrot_visualizer::ui
