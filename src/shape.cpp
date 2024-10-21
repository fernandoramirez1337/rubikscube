#include "shape.hpp"

ogl::shape::shape() {
  center = ogl::point(0.0f, 0.0f, 0.0f);
}

ogl::shape::~shape() {
  
}

void ogl::shape::get_vertices(float* ve) const {
  for (size_t i = 0; i < vertices.size(); ++i) {
    size_t index = i * 3;
    ve[index] = vertices[i].x;
    ve[index + 1] = vertices[i].y;
    ve[index + 2] = vertices[i].z;
  } 
}

void ogl::shape::get_indices(unsigned int* in, size_t base) const {
  for (size_t i = 0; i < indices[base].size(); ++i) {
    in[i] = indices[base][i];
  }
}

void ogl::shape::add_vertex(const ogl::point& v) {
  vertices.push_back(v);
}

void ogl::shape::add_index(const std::vector<unsigned int>& i) {
  indices.push_back(i);
}
