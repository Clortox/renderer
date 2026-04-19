#include "model.h"
#include "tgaimage.h"
#include <cmath>
#include <iostream>
#include <print>

// BGRA order
constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void line(int ax, int ay, int bx, int by, TGAImage &framebuffer,
          TGAColor color) {
  bool steep = std::abs(ax - bx) < std::abs(ay - by);

  if (steep) {
    std::swap(ax, ay);
    std::swap(bx, by);
  }

  if (ax > bx) {
    std::swap(ax, bx);
    std::swap(ay, by);
  }

  for (int x = ax; x <= bx; ++x) {
    float t = (x - ax) / static_cast<float>(bx - ax);
    int y = std::round(ay + (by - ay) * t);

    if (steep) {
      framebuffer.set(y, x, color);
    } else {
      framebuffer.set(x, y, color);
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Bad usage" << std::endl;
    return -1;
  }

  std::string modelPath(argv[1]);
  std::cout << "Opening Model " << modelPath << std::endl;

  Model model(modelPath);

  constexpr int width = 1920;
  constexpr int height = 1080;

  TGAImage framebuffer(width, height, TGAImage::RGB);

  float scaleFactor = 1.0f;
  std::vector<vec3i> triangles = model.getTriangles();

  std::cout << "triangles " << triangles.size() << std::endl;

  for (int i = 0; i < triangles.size(); ++i) {
    vec3i triangle = triangles[i];

    // std::cout << "trinagle " << triangle.x << " " << triangle.y << " "
    //           << triangle.z << std::endl;

    vec3f x = model.getVertex(triangle.x);
    vec3f y = model.getVertex(triangle.y);
    vec3f z = model.getVertex(triangle.z);

    x.x += 1;
    x.x *= width / 2;
    x.y += 1;
    x.y *= height / 2;

    y.x += 1;
    y.x *= width / 2;
    y.y += 1;
    y.y *= height / 2;

    z.x += 1;
    z.x *= width / 2;
    z.y += 1;
    z.y *= height / 2;

    line(x.x * scaleFactor, x.y * scaleFactor, y.x * scaleFactor,
         y.y * scaleFactor, framebuffer, red);
    line(x.x * scaleFactor, x.y * scaleFactor, z.x * scaleFactor,
         z.y * scaleFactor, framebuffer, red);
    line(z.x * scaleFactor, z.y * scaleFactor, y.x * scaleFactor,
         y.y * scaleFactor, framebuffer, red);
  }

  framebuffer.write_tga_file("framebuffer.tga");
  return 0;
}
