#ifndef MYSHAPES_HPP
#define MYSHAPES_HPP

#include "shape.hpp"
#include "mylib.hpp"
#include <vector>

ogl::translation moveRight(0.1f, 0.0f, 0.0f);
ogl::translation moveLeft(-0.1f, 0.0f, 0.0f);
ogl::translation moveUp(0.0f, 0.1f, 0.0f);
ogl::translation moveDown(0.0f, -0.1f, 0.0f);
ogl::scale scaleDown(0.90f, 0.90f, 1.0f);
ogl::scale scaleUp(1.1f, 1.1f, 1.0f);
ogl::rotate_z rotateZ(0.1f);
ogl::rotate_z rotateZ_(-0.1f);

ogl::shape testShape;

void create_testShape() {
  testShape.add_vertex(ogl::point(-0.5f, -0.5f, 0.0f));
  testShape.add_vertex(ogl::point(0.5f, -0.5f, 0.0f));
  testShape.add_vertex(ogl::point(0.0f, 0.5f, 0.0f));
  testShape.add_index(std::vector<unsigned int>{0, 1, 2});
  testShape.update_center();
}

#endif