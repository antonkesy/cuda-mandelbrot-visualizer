#include "window.hpp"

#include <cstdlib>

namespace mandelbrot_visualizer::ui {

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
int display_w{};
int display_h{};
Selection selection_area{};
bool reset_area{};
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

void DrawRectangle() {
  glBegin(GL_QUADS);
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  glColor4f(1.0F, 1.0F, 1.0F, 0.5F);  // RGBA color with alpha (transparency)
  float x0 = -1.0F + 2.0F * (static_cast<float>(selection_area.area.start_x) /
                             static_cast<float>(display_w));
  float x1 = -1.0F + 2.0F * (static_cast<float>(selection_area.area.end_x) /
                             static_cast<float>(display_w));
  float y0 = 1.0F - 2.0F * (static_cast<float>(selection_area.area.start_y) /
                            static_cast<float>(display_h));
  float y1 = 1.0F - 2.0F * (static_cast<float>(selection_area.area.end_y) /
                            static_cast<float>(display_h));
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

  glVertex2f(x0, y0);
  glVertex2f(x1, y0);
  glVertex2f(x1, y1);
  glVertex2f(x0, y1);

  glEnd();
}

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

void Window::EndlessRender(
    const std::function<void()>& imgui_components,
    const std::function<void(const WindowInfo&)>& on_render) {
  while (glfwWindowShouldClose(window_) == 0) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    imgui_components();

    ImGui::Render();
    glfwGetFramebufferSize(window_, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    // TOOD(ak): check if selection area is bigger than few pixels
    on_render(
        {display_w, display_h,
         (selection_area.has_selected ? std::make_optional(selection_area.area)
                                      : std::nullopt),
         reset_area});

    selection_area.has_selected = false;

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (selection_area.selecting) {
      DrawRectangle();
    }

    glfwSwapBuffers(window_);

    reset_area = false;
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

  // Enable transparency
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  const auto key_callback = [](GLFWwindow* window, int key, int /*scancode*/,
                               int action, int /*mods*/) {
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
      reset_area = true;
    }
  };
  glfwSetKeyCallback(window_, key_callback);

  const auto mouse_button_callback = [](GLFWwindow* window, int button,
                                        int action, int /*mods*/) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      if (action == GLFW_PRESS) {
        double mouse_x{};
        double mouse_y{};
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        selection_area.area.start_x = static_cast<int>(mouse_x);
        selection_area.area.start_y = static_cast<int>(mouse_y);
        selection_area.area.end_x = static_cast<int>(mouse_x);
        selection_area.area.end_y = static_cast<int>(mouse_y);
        selection_area.selecting = true;
        selection_area.has_selected = false;
      } else if (action == GLFW_RELEASE) {
        selection_area.selecting = false;
        selection_area.has_selected = true;
      }
    }
  };
  glfwSetMouseButtonCallback(window_, mouse_button_callback);

  const auto cursor_pos_callback = [](GLFWwindow* /*window*/, double xpos,
                                      double ypos) {
    if (selection_area.selecting) {
      selection_area.area.end_x = static_cast<int>(xpos);
      selection_area.area.end_y = static_cast<int>(ypos);
    }
  };

  glfwSetCursorPosCallback(window_, cursor_pos_callback);
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
