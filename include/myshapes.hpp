#pragma once

#include <vector>

#include "mylib.hpp"

#define FLOATS_PER_VERTEX 8

class shape {
public:
  bool triangles, lines, textures;
  std::vector<point> points;
  std::vector<unsigned int> indicesLines, indicesTriangles;
  std::vector<float> vertices;
  point center;

  unsigned int EBO_Triangles, EBO_Lines, VAO, VBO, TXT;

  shape(bool l = true, bool t = true, bool tx = false) : lines(l), triangles(t), textures(tx) {};
  ~shape();
  void build();
  void load_txt(const char *);
  void load_points();
  void update_buffer();
  void update_center();
  void bind_textures();

  shape& operator*=(const matrix&);
  shape operator*(const matrix&) const;

  void pretty_transform(const matrix&);
  void transform_around(const matrix&, const point&);
  bool is_initialized() const { return VAO != 0; }
};