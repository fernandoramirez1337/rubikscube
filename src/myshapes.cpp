#include "myshapes.hpp"

#include <iostream>
#include <numeric>  //  std::accumulate
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int load_texture(const char* path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
  }
  stbi_image_free(data);
  return textureID;
}

// ------------------------------
// Shape class
// ------------------------------

shape::~shape() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO_Lines);
  glDeleteBuffers(1, &EBO_Triangles);
}

void shape::build() {
  load_points();
  update_center();
  glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);	

  if (lines) {
    glGenBuffers(1, &EBO_Lines);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Lines);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLines.size() * sizeof(unsigned int), indicesLines.data(), GL_STATIC_DRAW);
  }
  
  if (triangles) {
    glGenBuffers(1, &EBO_Triangles);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Triangles);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesTriangles.size() * sizeof(unsigned int), indicesTriangles.data(), GL_STATIC_DRAW);
  }

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);		

  if (textures) {
    //glBindTexture(GL_TEXTURE_2D, TXT);
  }
}

void shape::load_txt(const char* path) {
  TXT = load_texture(path);
}

void shape::load_points() {
  const size_t components_per_vertex = 8;
  if (vertices.size() % components_per_vertex != 0) {
    std::cerr << "Error: Vertices size must be a multiple of 8.\n";
    return;
  }

  const size_t n_points = vertices.size() / components_per_vertex;
  points.resize(n_points);

  for (size_t i = 0; i < n_points; ++i) {
    float x = vertices[i * components_per_vertex + 0];
    float y = vertices[i * components_per_vertex + 1];
    float z = vertices[i * components_per_vertex + 2];
    points[i] = point(x, y, z);
  }
}

void shape::update_buffer() {
  const size_t components_per_vertex = 8;
  if (vertices.size() != points.size() * components_per_vertex) {
    std::cerr << "Error: Size mismatch between vertices and points.\n";
    return;
  }

  const size_t n_points = points.size();
  for (size_t i = 0; i < n_points; ++i) {
    vertices[i * components_per_vertex + 0] = points[i].x;
    vertices[i * components_per_vertex + 1] = points[i].y;
    vertices[i * components_per_vertex + 2] = points[i].z;
    std::cout << vertices[i * components_per_vertex + 0] <<" "<<vertices[i * components_per_vertex + 1] <<" "<< vertices[i * components_per_vertex + 2] << std::endl;

  }
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
  glBindBuffer(GL_ARRAY_BUFFER, 0);		
}

void shape::update_center() {
  center = std::accumulate(points.begin(), points.end(), point(),
    [](const point& acc, const point& v) {
      return point(acc.x + v.x, acc.y + v.y, acc.z + v.z);
    });
  const float inv_size = 1.0f / points.size();
  center.x *= inv_size;
  center.y *= inv_size;
  center.z *= inv_size;
}

void shape::bind_textures() {
  if(textures)
	glBindTexture(GL_TEXTURE_2D, TXT);
}

shape& shape::operator*=(const matrix& transform) {
  for (auto& point : points) {
    std::cout  << std::endl;
    std::cout << point.x <<" "<< point.y <<" "<<  point.z << std::endl;
    point = transform * point;
    std::cout << point.x <<" "<< point.y <<" "<<  point.z << std::endl;
  }
  center = transform * center;
  return *this;
}

shape shape::operator*(const matrix& transform) const {
  shape result = *this;
  result *= transform;
  return result;
}

void shape::pretty_transform(const matrix& transform) {
  const point current_center = center;
  *this *= translation(-current_center.x, -current_center.y, -current_center.z);
  *this *= transform;
  *this *= translation(current_center.x, current_center.y, current_center.z);
  update_center();
}

void shape::transform_around(const matrix& transform, const point& p) {
  *this *= translation_inv(p.x, p.y, p.z);
  *this *= transform;
  *this *= translation(p.x, p.y, p.z);
  update_center();
}