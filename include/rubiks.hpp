#pragma once

#include <array>
#include <memory>
#include "myshapes.hpp"

class cube : public shape {
  public:
  cube(const point&, float);
};

class rubiks {
  public:
  rubiks(const point&, float);
  point center;
  std::array<std::unique_ptr<cube>, 26> pieces;
  void build();
  void update_buffer();
  void pretty_transform(const matrix&);
};