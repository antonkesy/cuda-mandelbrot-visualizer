#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace mandelbrot_visualizer::ui {

enum class Mode { kSequential, kParallel };

class Menu {
 public:
  static Mode ShowMenu();

 private:
  static Mode ModeCombo();
  static void FpsInfo();
};
}  // namespace mandelbrot_visualizer::ui
