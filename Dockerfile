# https://hub.docker.com/r/nvidia/cuda
FROM nvidia/cuda:12.3.0-runtime-ubuntu22.04

ENV TZ=Europe
ENV DEBIAN_FRONTEND noninteractive

WORKDIR /cuda_mandelbrot_visualizer

RUN apt-get update -y
RUN apt-get install -y software-properties-common 
RUN add-apt-repository universe -y
RUN apt-get install -y clang cmake # Building
RUN apt-get install -y freeglut3-dev # OpenGL
RUN apt-get install -y build-essential libxmu-dev libxi-dev libgl-dev # GLEW
RUN apt-get install -y xorg-dev # GLFW

COPY . /cuda_mandelbrot_visualizer
RUN rm -rf build

RUN mkdir build -p
WORKDIR /cuda_mandelbrot_visualizer/build
RUN cmake ..
RUN cmake --build .
