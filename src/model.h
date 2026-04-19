#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

struct vec3f {
  float x;
  float y;
  float z;
};

struct vec3i {
  unsigned int x;
  unsigned int y;
  unsigned int z;
};

class Model {
  std::vector<vec3f> verticies;
  std::vector<vec3i> triangles;

  void parseFile(std::ifstream &);
  vec3f parseVertex(std::string &);
  vec3i parseTriangle(std::string &);

public:
  Model(std::string &);
  vec3f getVertex(long);
  std::vector<vec3i> &getTriangles();
};
