# Mandelbrot Visualizer

## Build and Execution

### Docker

build:

```
docker compose build mandelbrot_visualizer
```

run with xorg:

```
xhost +local:docker || true
docker compose run --rm mandelbrot_visualizer
```

### Natively

## Dependencies

- OpenGL
- Cuda
- CMake
- C++11

_See docker container for Ubuntu/Debian install steps_

#### Build

```
mkdir build -p
cd build
cmake ..
cmake --build .
```

#### Execution

```
./mandelbrot_visualizer
```

## Development

- pre-commit
- docker
