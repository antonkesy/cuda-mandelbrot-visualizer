#include "menu.hpp"

#include <fmt/core.h>

#include <string>
#include <vector>

namespace mandelbrot_visualizer::ui {

void Menu::ShowMenu(VisualizerState& state) {
  constexpr auto kVSpace = 10.0F;
  ImGui::NewFrame();
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::Begin("Render Settings");
  WindowInfo(state);
  DurationInfo(state);
  FpsInfo();
  ImGui::Dummy(ImVec2(0.0F, kVSpace));
  ModeCombo(state.mode);
  SetMaxIterations(state.max_iterations);
  SetColor(state.base_color);
  ImGui::Dummy(ImVec2(0.0F, kVSpace));
  InteractionInfo();
  ImGui::End();
}

void Menu::ModeCombo(Mode& current) {
  static std::vector<std::string> items = {"Sequential", "OpenMP"};
  auto current_item = static_cast<int>(current);

  if (ImGui::BeginCombo("##combo", items[current_item].c_str())) {
    for (int i = 0; i < 2; i++) {
      const bool is_selected = (current_item == i);
      if (ImGui::Selectable(items[i].c_str(), is_selected)) current_item = i;
      if (is_selected) ImGui::SetItemDefaultFocus();
    }

    ImGui::EndCombo();
  }
  current = static_cast<Mode>(current_item);
}

void Menu::FpsInfo() {
  ImGuiIO& io = ImGui::GetIO();

  constexpr auto kToMs = 1000.0F;
  ImGui::Text(  // NOLINT(cppcoreguidelines-pro-type-vararg)
      "Application average %.3f ms/frame (%.1f FPS)", kToMs / io.Framerate,
      io.Framerate);
}

void Menu::DurationInfo(VisualizerState& state) {
  const auto text =
      fmt::format("Compute Progress: {:.1f}/100", *state.progress * 100);
  ImGui::ProgressBar(*state.progress, ImVec2(-1, 0), text.c_str());
  ImGui::Text(  // NOLINT(cppcoreguidelines-pro-type-vararg)
      "Compute Time: %.1lims, Draw Time: %.1lims", state.compute_time.count(),
      state.draw_time.count());
}

void Menu::WindowInfo(VisualizerState& state) {
  ImGui::Text(  // NOLINT(cppcoreguidelines-pro-type-vararg)
      "Window Size: %ix%i", state.display_width, state.display_height);
}

void Menu::SetColor(RGBColor& current) {
  ImGui::ColorEdit3("Base Color", current.data());
}

void Menu::SetMaxIterations(int& current) {
  constexpr auto kMin = 0;
  constexpr auto kMax = 1000;
  ImGui::SliderInt("Max Iterations", &current, kMin, kMax);
}

void Menu::InteractionInfo() {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  ImGui::Text("Quit: <ESC>/<Q>\nZoom: Select area with mouse\nReset: <R>");
}
}  // namespace mandelbrot_visualizer::ui
