#include "mylib.hpp"

#include <array>
#include <cmath>
#include <iostream>

// ------------------------------
// vector class
// ------------------------------

float vector::length() const {
  return std::sqrt(x*x + y*y + z*z);
}

vector vector::normalize() const {
  float len = length();
  return (len != 0.0f) ? vector(x / len, y / len, z / len) : *this;
}

float vector::dot(const vector& v) const {
  return x * v.x + y * v.y + z * v.z;
}

vector vector::cross(const vector& v) const {
  return vector(
    y * v.z - z * v.y,
    z * v.x - x * v.z,
    x * v.y - y * v.x
  );
}

// ------------------------------
// point class
// ------------------------------


// ------------------------------
// matrix class
// ------------------------------

matrix::matrix() {
  set_identity();
}

matrix matrix::operator*(const matrix& mat) const {
  matrix result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.m[i][j] = 0.0f;
      for (int k = 0; k < 4; ++k) {
        result.m[i][j] += m[i][k] * mat.m[k][j];
      }
    }
  }
  return result;
}

matrix& matrix::operator*=(const matrix& mat) {
  *this = *this * mat;
  return *this;
}

point matrix::operator*(const point& poi) const {
  float x[4] = {poi.x, poi.y, poi.z, 1.0f};
  float result[4] = {0.0f};

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result[i] += m[i][j] * x[j];
    }
  }

  float w_inv = (result[3] != 0.0f) ? 1.0f / result[3] : 1.0f;
  return point(result[0] * w_inv, result[1] * w_inv, result[2] * w_inv);
  std::cout << result[0] * w_inv << std::endl;
}

void matrix::set_identity() {
  m = {{
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};
}

void matrix::set(const matrix4& mat) {
  m = mat;
}

const matrix4& matrix::get() const {
  return m;
}

matrix matrix::transpose() const {
  matrix result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.m[i][j] = m[j][i];
    }
  }
  return result;
}

// ------------------------------
// Scale matrix
// ------------------------------

scale::scale(float x, float y, float z) : matrix() {
  m[0][0] = x;
  m[1][1] = y;
  m[2][2] = z;
}

scale_inv::scale_inv(float x, float y, float z) : matrix() {
  if (x == 0.0f || y == 0.0f || z == 0.0f) {
    throw std::invalid_argument("Scaling values cannot be zero.");
  }
  m[0][0] = 1.0f / x;
  m[1][1] = 1.0f / y;
  m[2][2] = 1.0f / z;
}

// ------------------------------
// Rotation matrices
// ------------------------------

rotate_x::rotate_x(float angle) : matrix() {
  float cos_a = std::cos(angle);
  float sin_a = std::sin(angle);

  m[1][1] = cos_a;
  m[1][2] = -sin_a;
  m[2][1] = sin_a;
  m[2][2] = cos_a;
}

rotate_x_inv::rotate_x_inv(float angle) : matrix() {
  float cos_a = std::cos(-angle);
  float sin_a = std::sin(-angle);

  m[1][1] = cos_a;
  m[1][2] = -sin_a;
  m[2][1] = sin_a;
  m[2][2] = cos_a;
}

rotate_y::rotate_y(float angle) : matrix() {
  float cos_a = std::cos(angle);
  float sin_a = std::sin(angle);

  m[0][0] = cos_a;
  m[0][2] = sin_a;
  m[2][0] = -sin_a;
  m[2][2] = cos_a;
}

rotate_y_inv::rotate_y_inv(float angle) : matrix() {
  float cos_a = std::cos(-angle);
  float sin_a = std::sin(-angle);

  m[0][0] = cos_a;
  m[0][2] = sin_a;
  m[2][0] = -sin_a;
  m[2][2] = cos_a;
}

rotate_z::rotate_z(float angle) : matrix() {
  float cos_a = std::cos(angle);
  float sin_a = std::sin(angle);

  m[0][0] = cos_a;
  m[0][1] = -sin_a;
  m[1][0] = sin_a;
  m[1][1] = cos_a;
}

rotate_z_inv::rotate_z_inv(float angle) : matrix() {
  float cos_a = std::cos(-angle);
  float sin_a = std::sin(-angle);

  m[0][0] = cos_a;
  m[0][1] = -sin_a;
  m[1][0] = sin_a;
  m[1][1] = cos_a;
}

// ------------------------------
// Translation matrix
// ------------------------------

translation::translation(float x, float y, float z) : matrix() {
  m[0][3] = x;
  m[1][3] = y;
  m[2][3] = z;
}

translation_inv::translation_inv(float x, float y, float z) : matrix() {
  m[0][3] = -x;
  m[1][3] = -y;
  m[2][3] = -z;
}
// ------------------------------
// Projection matrix
// ------------------------------
/*
projection::projection(float fov, float aspect, float near, float far) : matrix() {
  float fov_rad = fov * M_PI / 180.0f;
  float tan_half_fov = std::tan(fov_rad / 2.0f);
  float range = far - near;

  m[0][0] = 1.0f / (aspect * tan_half_fov);
  m[1][1] = 1.0f / tan_half_fov;
  m[2][2] = -(far + near) / range;
  m[2][3] = -2.0f * far * near / range;
  m[3][2] = -1.0f;
  m[3][3] = 0.0f;
}
*/
