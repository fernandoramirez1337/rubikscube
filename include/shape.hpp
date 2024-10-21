#ifndef OGL_SHAPE_HPP
#define OGL_SHAPE_HPP

#include "mylib.hpp"
#include <vector>

namespace ogl {

class shape {
public:
  std::vector<ogl::point> vertices;
  ogl::point center;
  std::vector<std::vector<unsigned int>> indices;

  std::vector<unsigned int> EBOs;
  std::vector<unsigned int> VAOs;
  std::vector<unsigned int> VBOs;

  shape();
  ~shape();

  void add_vertex(const ogl::point&);
  void add_index(const std::vector<unsigned int>&);

  void get_vertices(float*) const;
  void get_indices(unsigned int*, size_t = 0) const;

  shape& operator*=(const matrix& transform) {
    for (auto& vertex : vertices) {
      vertex = transform * vertex;
    }
    center = transform * center;
    return *this;
  }

  [[nodiscard]] shape operator*(const matrix& transform) const {
    shape result = *this;
    result *= transform;
    return result;
  }

  void rotate_around_center(const ogl::rotate_z& rotation_matrix) {
    // Store the current center
    ogl::point currentCenter = center;

    // Translate to origin
    *this *= ogl::translation(-center.x, -center.y, -center.z);
    
    // Apply rotation
    *this *= rotation_matrix;
    
    *this *= ogl::translation(currentCenter.x, currentCenter.y, currentCenter.z);

    center = currentCenter;
  }

  void update_center() {
    center = ogl::point(0.0f, 0.0f, 0.0f);
    for (const auto& vertex : vertices) {
      center.x += vertex.x;
      center.y += vertex.y;
      center.z += vertex.z;
    }
    center.x /= vertices.size();
    center.y /= vertices.size();
    center.z /= vertices.size();
  }

  void scale_around_center(const ogl::scale& scale_matrix) {
    ogl::point currentCenter = center;

    *this *= ogl::translation(-center.x, -center.y, -center.z);
    *this *= scale_matrix;
    *this *= ogl::translation(currentCenter.x, currentCenter.y, currentCenter.z);

  }
};

}

#endif