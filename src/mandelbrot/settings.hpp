#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <complex>
#include <memory>

#include "../ui/color.hpp"

namespace mandelbrot_visualizer {

struct Settings {
  struct Area {
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
    std::complex<double> start{-2.0F, -1.0F};
    std::complex<double> end{1.0F, 1.0F};
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

    bool operator!=(const Area& other) const {
      return start != other.start || end != other.end;
    }
  };
  int height;
  int width;
  ui::RGBColor base_color;
  int max_iterations;
  std::shared_ptr<float> progress;
  Area area;
};

;

}  // namespace mandelbrot_visualizer
