#pragma once

#include <array>
#include <memory>
#include "myshapes.hpp"

class cube : public shape {
  public:
  cube(const point&, float);
  // 0 0 0 0 0 0 texture F B L R U D
  //cube(const point&, float, unsigned int);
  cube(const point&, float, unsigned int, bool, bool, bool, bool, bool, bool);
};

class rubiks {
  public:
  rubiks(const point&, float, unsigned int);
  point center;
  std::array<std::unique_ptr<cube>, 26> pieces;
  void build();
  void update_buffer();
  void pretty_transform(const matrix&);
};