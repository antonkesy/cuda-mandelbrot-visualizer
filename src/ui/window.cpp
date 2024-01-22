#include "window.hpp"

#include <cstdlib>

namespace mandelbrot_visualizer::ui {

Window::Window(const std::string& name, int width, int height) {
  SetupGLFW(width, height, name);
  SetupImGui();
}

Window::~Window() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}

void Window::EndlessRender(const std::function<void()>& imgui_components,
                           const std::function<void(int, int)>& on_render) {
  while (glfwWindowShouldClose(window_) == 0) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    imgui_components();

    ImGui::Render();
    int display_w{};
    int display_h{};
    glfwGetFramebufferSize(window_, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    on_render(display_w, display_h);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window_);
  }
}

void Window::SetupGLFW(int width, int height, const std::string& name) {
  if (glfwInit() == 0) {
    std::exit(-1);  // NOLINT(concurrency-mt-unsafe)
  }

  window_ = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
  if (window_ == nullptr) {
    glfwTerminate();
    std::exit(-1);  // NOLINT(concurrency-mt-unsafe)
  }

  glfwMakeContextCurrent(window_);
  glfwSetWindowAspectRatio(window_, 1, 1);
}

void Window::SetupImGui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui_ImplGlfw_InitForOpenGL(window_, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

}  // namespace mandelbrot_visualizer::ui
