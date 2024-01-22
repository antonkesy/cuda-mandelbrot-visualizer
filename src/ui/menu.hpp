#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "mode.hpp"
#include "state.hpp"

namespace mandelbrot_visualizer::ui {

struct MenuValues {
  Mode mode;
  RGBColor base_color;
};

class Menu {
 public:
  static MenuValues ShowMenu(const MenuState& state);

 private:
  static Mode ModeCombo(Mode current);
  static void FpsInfo();
  static void DurationInfo(const MenuState& state);
  static void WindowInfo(const MenuState& state);
  static void SetColor(RGBColor& current);
};

}  // namespace mandelbrot_visualizer::ui
