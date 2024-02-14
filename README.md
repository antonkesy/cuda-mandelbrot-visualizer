# Mandelbrot Visualizer

Quick and dirty [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) Visualizer in modernish C++ built to pass time and apply knowledge.

<img src='./docs/screenshot.png' width='625'>

## Used Technologies

- C++11/17/20 Features (Threads, Futures, Lambdas, ...)
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)/[tidy](https://clang.llvm.org/extra/clang-tidy/)
- [CMake](https://cmake.org/)
- [GoogleTest](https://github.com/google/googletest)
- [Benchmark](https://github.com/google/benchmark)
- [OpenMP](https://www.openmp.org/)
- [imgui](https://github.com/ocornut/imgui)
- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [Docker](https://www.docker.com/)
- [fmt](https://github.com/fmtlib/fmt)
- [pre-commit](https://pre-commit.com/)

## Build and Execution

### Docker

Run GUI with xorg:

```
xhost +local:docker || true
docker compose run --rm mandelbrot_visualizer
<OR>
docker compose run --rm nvidia_mandelbrot_visualizer
```

### Natively

## Dependencies

- OpenGL
- CMake 3.11+
- C++20+
- OpenMP

All other dependencies are built from source through external submodules.

_See docker container for example Ubuntu/Debian install steps_

#### Build

```
mkdir build -p
cd build
cmake ..
cmake --build .
```

#### Execution

```
export OMP_CANCELLATION=true # enable OpenMP cancellation for redrawing -> program tries to bootstrap it anyway
./mandelbrot_visualizer
```

## Development

```
pre-commit install
```

[GitHub Action](https://docs.github.com/en/actions) enabled which runs [pre-commit](https://pre-commit.com/) on main merge request.
