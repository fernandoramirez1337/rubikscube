#pragma once

#include <array>
#include <cmath>

const float cero = 0.0f;
class vector {
public:
  float x, y, z;

  vector(float x_ = cero, float y_ = cero, float z_ = cero)  : x(x_), y(y_), z(z_) {}
  vector(const vector&)  = default;
  ~vector() = default;
  vector& operator=(const vector&) = default;

  float length() const;
  vector normalize() const;
  float dot(const vector&) const;
  vector cross(const vector&) const;
};

class point {
public:
  float x, y, z;

  point(float x_ = cero, float y_ = cero, float z_ = cero)  : x(x_), y(y_), z(z_) {}
  point(const point&)  = default;
  ~point() = default;
  point& operator=(const point&) = default;
};

const unsigned long cuatro = 4ul;
using matrix4 = std::array<std::array<float, cuatro>, cuatro>;
class matrix {
protected:
  matrix4 m;

public:
  matrix();

  matrix operator*(const matrix&) const;
  matrix& operator*=(const matrix&);
  point operator*(const point&) const;

  void set_identity();
  void set(const matrix4&);
  const matrix4& get() const;
  matrix transpose() const;
};

class scale : public matrix {
public:
  scale(float,float,float);
};

class rotate_x : public matrix {
public:
  explicit rotate_x(float);
};

class rotate_y : public matrix {
public:
  explicit rotate_y(float);
};

class rotate_z : public matrix {
public:
  explicit rotate_z(float);
};

class translation : public matrix {
public:
  translation(float,float,float);
};

class scale_inv : public matrix {
public:
  scale_inv(float,float,float);
};

class rotate_x_inv : public matrix {
public:
  explicit rotate_x_inv(float);
};

class rotate_y_inv : public matrix {
public:
  explicit rotate_y_inv(float);
};

class rotate_z_inv : public matrix {
public:
  explicit rotate_z_inv(float);
};

class translation_inv : public matrix {
public:
  translation_inv(float,float,float);
};