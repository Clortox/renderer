# Renderer

A simple single image renderer, written in C++. CPU (for now), just for my learning.

From following [this](https://haqr.eu/tinyrenderer/) very good course.

## Sample images

![Wireframe](./output/wireframe-armadillo.png)
![Wireframe](./output/wireframe-head.png)

Wireframe Rendering

## Building

```bash
mkdir build && cd build && cmake ..
make
./src/renderer ../tests/diablo3_pose.obj

```
