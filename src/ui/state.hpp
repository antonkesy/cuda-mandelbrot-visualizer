#pragma once

#include <chrono>

#include "mode.hpp"
namespace mandelbrot_visualizer::ui {

using std::chrono::milliseconds;

struct MenuState {
  Mode mode = Mode::kSequential;
  milliseconds compute_time;
  milliseconds draw_time;
  int display_width = 0;
  int display_height = 0;

  bool operator==(const MenuState& other) const {
    return mode == other.mode && compute_time == other.compute_time &&
           draw_time == other.draw_time &&
           display_width == other.display_width &&
           display_height == other.display_height;
  }
  bool operator!=(const MenuState& other) const { return !(*this == other); }
};

}  // namespace mandelbrot_visualizer::ui
