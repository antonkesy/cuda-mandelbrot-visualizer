cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(mandelbrot_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(OpenGL REQUIRED)
find_package(OpenMP REQUIRED)

add_subdirectory(external/googletest)
add_subdirectory(external/benchmark)
add_subdirectory(external/fmt)
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

# TODO: split dependencies better

add_library(
  mandelbrot_lib src/mandelbrot/mandelbrot.cpp src/mandelbrot/sequential.cpp
                 src/mandelbrot/openmp.cpp ${IMGUI_SOURCES})
target_include_directories(mandelbrot_lib PUBLIC ${IMGUI_PATH}
                                                 ${IMGUI_PATH}/backends)
target_link_libraries(mandelbrot_lib PUBLIC libglew_static OpenGL::GL glfw
                                            OpenMP::OpenMP_CXX fmt::fmt)

set(VISUALIZER_SRC src/main.cpp src/ui/menu.cpp src/ui/window.cpp)
add_executable(${PROJECT_NAME} ${VISUALIZER_SRC} ${IMGUI_SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  mandelbrot_lib
  glfw
  libglew_static
  OpenGL::GL
  OpenMP::OpenMP_CXX
  fmt::fmt)

target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_PATH}
                                                   ${IMGUI_PATH}/backends)

target_compile_definitions(${PROJECT_NAME}
                           PRIVATE IMGUI_IMPL_OPENGL_LOADER_GL3W)

add_subdirectory(benchmarks)
add_subdirectory(tests)
