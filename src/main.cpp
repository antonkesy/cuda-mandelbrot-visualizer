#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main() {
  if (glfwInit() == 0) {
    return -1;
  }

  const auto width = 1200;
  const auto height = 900;
  GLFWwindow *window = glfwCreateWindow(
      width, height, "Cuda Mandelbrot Visualizer", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  while (glfwWindowShouldClose(window) == 0) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello, GLFW!");
    ImGui::Text("Hello, world!");  // NOLINT(cppcoreguidelines-pro-type-vararg)
    ImGui::End();

    ImGui::Render();
    int display_w{};
    int display_h{};
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();

  return 0;
}
