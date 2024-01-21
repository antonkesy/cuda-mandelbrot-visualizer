#pragma once

#include <chrono>

#include "mode.hpp"
namespace mandelbrot_visualizer::ui {

using std::chrono::milliseconds;

struct MenuState {
  Mode mode = Mode::kSequential;
  milliseconds compute_time{};
  milliseconds draw_time{};
  int display_width{};
  int display_height{};
  bool is_computing{};

  [[nodiscard]] bool NeedsRecomputation(const MenuState& other) const {
    return mode != other.mode || display_width != other.display_width ||
           display_height != other.display_height;
  }
};

}  // namespace mandelbrot_visualizer::ui
