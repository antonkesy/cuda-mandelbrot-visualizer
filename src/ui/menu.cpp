#include "menu.hpp"

#include <string>
#include <vector>

namespace mandelbrot_visualizer::ui {

Mode Menu::ShowMenu() {
  ImGui::NewFrame();
  ImGui::Begin("Render Settings");
  const auto mode = ModeCombo();
  // TODO(ak): add compute time
  FpsInfo();

  ImGui::End();
  return mode;
}

Mode Menu::ModeCombo() {
  std::vector<std::string> items = {"Sequential", "Parallel"};
  int current_item = 0;

  if (ImGui::BeginCombo("##combo", items[current_item].c_str())) {
    for (int i = 0; i < 2; i++) {
      const bool is_selected = (current_item == i);
      if (ImGui::Selectable(items[i].c_str(), is_selected)) current_item = i;
      if (is_selected) ImGui::SetItemDefaultFocus();
    }

    ImGui::EndCombo();
  }
  return static_cast<Mode>(current_item);
}

void Menu::FpsInfo() {
  ImGuiIO& io = ImGui::GetIO();

  ImGui::Text(  // NOLINT(cppcoreguidelines-pro-type-vararg)
      "Application average %.3f ms/frame (%.1f FPS)",
      // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
      1000.0F / io.Framerate, io.Framerate);
}

}  // namespace mandelbrot_visualizer::ui
