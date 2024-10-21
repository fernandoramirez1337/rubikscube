#include "mylib.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>

// ------------------------------
// Implementation of class `vector`
// ------------------------------
float ogl::vector::length() const noexcept {
  return std::sqrt(x*x + y*y + z*z);
}

ogl::vector ogl::vector::normalize() const noexcept {
  float len = length();
  return (len != 0.0f) ? ogl::vector(x / len, y / len, z / len) : *this;
}

float ogl::vector::dot(const vector& v) const noexcept {
  return x * v.x + y * v.y + z * v.z;
}

ogl::vector ogl::vector::cross(const vector& v) const noexcept {
  return ogl::vector(
    y * v.z - z * v.y,
    z * v.x - x * v.z,
    x * v.y - y * v.x
  );
}

// ------------------------------
// Implementation of class `point`
// ------------------------------
// ogl::point& ogl::point::operator=(const ogl::point& other) noexcept {
//   if (this != &other) {
//     x = other.x;
//     y = other.y;
//     z = other.z;
//   }
//   return *this;
// }

// ------------------------------
// Implementation of class `matrix`
// ------------------------------
ogl::matrix::matrix() noexcept {
  set_identity();
}

[[nodiscard]] ogl::matrix ogl::matrix::operator*(const ogl::matrix& mat) const noexcept {
  ogl::matrix result;
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

ogl::matrix& ogl::matrix::operator*=(const ogl::matrix& mat) noexcept {
  *this = *this * mat;
  return *this;
}

[[nodiscard]] ogl::point ogl::matrix::operator*(const ogl::point& poi) const noexcept {
  float x[4] = {poi.x, poi.y, poi.z, 1.0f};
  float result[4] = {0.0f};

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result[i] += m[i][j] * x[j];
    }
  }

  float w_inv = (result[3] != 0.0f) ? 1.0f / result[3] : 1.0f;
  return ogl::point(result[0] * w_inv, result[1] * w_inv, result[2] * w_inv);
}

[[nodiscard]] ogl::matrix ogl::matrix::transpose() const noexcept {
  ogl::matrix result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.m[i][j] = m[j][i];
    }
  }
  return result;
}

void ogl::matrix::set_identity() noexcept {
  m = {{
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};
}

[[nodiscard]] const ogl::matrix4& ogl::matrix::get() const noexcept {
  return m;
}

void ogl::matrix::set(const ogl::matrix4& mat) noexcept {
  m = mat;
}

// ------------------------------
// Scale matrix
// ------------------------------
ogl::scale::scale(float sx, float sy, float sz) noexcept : matrix() {
  m[0][0] = sx;
  m[1][1] = sy;
  m[2][2] = sz;
}

// ------------------------------
// Rotation matrices
// ------------------------------
ogl::rotate_x::rotate_x(float angle) noexcept : matrix() {
  float cos_a = std::cos(angle);
  float sin_a = std::sin(angle);

  m[1][1] = cos_a;
  m[1][2] = -sin_a;
  m[2][1] = sin_a;
  m[2][2] = cos_a;
}

ogl::rotate_y::rotate_y(float angle) noexcept : matrix() {
  float cos_a = std::cos(angle);
  float sin_a = std::sin(angle);

  m[0][0] = cos_a;
  m[0][2] = sin_a;
  m[2][0] = -sin_a;
  m[2][2] = cos_a;
}

ogl::rotate_z::rotate_z(float angle) noexcept : matrix() {
  float cos_a = std::cos(angle);
  float sin_a = std::sin(angle);

  m[0][0] = cos_a;
  m[0][1] = -sin_a;
  m[1][0] = sin_a;
  m[1][1] = cos_a;
}

// ------------------------------
// Translation matrix
// ------------------------------
ogl::translation::translation(float tx, float ty, float tz) noexcept : matrix() {
  m[0][3] = tx;
  m[1][3] = ty;
  m[2][3] = tz;
}
 