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
    std::complex<double> start;
    std::complex<double> end;

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
