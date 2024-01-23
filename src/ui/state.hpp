#pragma once

#include <chrono>
#include <memory>

#include "../mandelbrot/settings.hpp"
#include "../ui/color.hpp"
#include "mode.hpp"

namespace mandelbrot_visualizer::ui {

using std::chrono::milliseconds;

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
  std::shared_ptr<float> progress = std::make_unique<float>(0.0F);  //[0,1]
  mandelbrot_visualizer::Settings::Area area{{-2.0F, -1.0F}, {1.0F, 1.0F}};
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

  [[nodiscard]] bool NeedsRecomputation(const VisualizerState& other) const {
    return mode != other.mode || display_width != other.display_width ||
           display_height != other.display_height ||
           base_color != other.base_color ||
           max_iterations != other.max_iterations || area != other.area;
  }
};

}  // namespace mandelbrot_visualizer::ui
