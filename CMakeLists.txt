cmake_minimum_required(VERSION 3.12)
project(cuda_mandelbrot_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/glew-cmake)

set(IMGUI_PATH external/imgui)
set(IMGUI_SOURCES
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp)

set(SOURCE_FILES
    src/main.cpp src/mandelbrot/mandelbrot.cpp src/mandelbrot/sequential.cpp
    src/ui/menu.cpp src/ui/window.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw libglew_static OpenGL::GL)

target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_PATH}
                                                   ${IMGUI_PATH}/backends)

target_compile_definitions(${PROJECT_NAME}
                           PRIVATE IMGUI_IMPL_OPENGL_LOADER_GL3W)
