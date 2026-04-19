#include "model.h"
#include <iterator>

Model::Model(std::string &path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "failed to open file";
    return;
  }

  this->parseFile(file);
}

void Model::parseFile(std::ifstream &stream) {
  std::string s;
  int i = 0;
  while (std::getline(stream, s)) {
    // vertex
    if (s.starts_with("v ")) {

      vec3f vec = this->parseVertex(s);
      this->verticies.push_back(vec);

    } else if (s.starts_with("f ")) {
      ++i;

      vec3i vec = this->parseTriangle(s);
      this->triangles.push_back(vec);

    } else {
      continue;
    }
  }
}

vec3f Model::parseVertex(std::string &s) {
  std::string currentVal;
  vec3f ret;
  int floats = 0;

  for (char c : s) {
    if (c == 'v') {
      continue;
    } else if (c == ' ' && !currentVal.empty()) {

      float f = std::stof(currentVal);

      switch (floats) {
      case 0:
        ret.x = f;
        break;
      case 1:
        ret.y = f;
        break;
      case 2:
        ret.z = f;
        break;
      }

      currentVal.clear();
      ++floats;
    } else {
      currentVal.push_back(c);
    }
  }

  return ret;
}

vec3i Model::parseTriangle(std::string &s) {
  std::string currentVal;
  std::string buffer;
  vec3i ret;
  int vecIndex = 0;

  for (char c : s) {
    if (c == 'f') {
      continue;
    } else if (c == ' ' && !currentVal.empty()) {
      // get up till the first slash
      for (char cc : currentVal) {
        if (cc != '/')
          buffer += cc;
        else
          break;
      }

      int i = std::stoi(buffer);
      switch (vecIndex) {
      case 0:
        ret.x = i;
        break;
      case 1:
        ret.y = i;
        break;
      case 2:
        ret.z = i;
        break;
      }

      buffer.clear();
      currentVal.clear();
      ++vecIndex;

    } else {
      currentVal.push_back(c);
    }
  }

  for (char cc : currentVal) {
    if (cc != '/')
      buffer += cc;
    else
      break;
  }

  ret.z = std::stoi(buffer);

  return ret;
}

vec3f Model::getVertex(long vertexId) {
  int index = vertexId - 1;

  return this->verticies[index];
}

std::vector<vec3i> &Model::getTriangles() { return this->triangles; }
