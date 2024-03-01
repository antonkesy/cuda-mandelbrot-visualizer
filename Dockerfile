# https://hub.docker.com/r/nvidia/cuda
FROM nvidia/cuda:12.3.0-runtime-ubuntu22.04 as base

ENV TZ=Europe
ENV DEBIAN_FRONTEND noninteractive

WORKDIR /mandelbrot_visualizer

# Build dependencies
RUN apt-get update -y
RUN apt-get install -y software-properties-common 
RUN add-apt-repository universe -y
RUN apt-get install -y clang cmake # Building
RUN apt-get install -y freeglut3-dev # OpenGL
RUN apt-get install -y build-essential libxmu-dev libxi-dev libgl-dev # GLEW
RUN apt-get install -y xorg-dev # GLFW

FROM base as build
COPY . /mandelbrot_visualizer
RUN rm -rf build

# Build
RUN mkdir build -p
WORKDIR /mandelbrot_visualizer/build
RUN cmake ..
RUN cmake --build .

FROM build as run
# OpenMP
ENV OMP_CANCELLATION=true

FROM run as test
# Run tests
WORKDIR /mandelbrot_visualizer/build/tests
RUN ctest

FROM test as ci
# pre-commit dependencies
RUN apt-get install -y git python3 python3-pip clang-format clang-tidy
RUN pip3 install pre-commit

# pre-commit
WORKDIR /mandelbrot_visualizer
RUN git init . && pre-commit install-hooks
RUN pre-commit run --all-files
