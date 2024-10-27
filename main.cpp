#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "workshop.cpp"
#include "myshaders.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 732;

int main() {
  std::vector<shape*> shapes;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  gladLoadGL();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  build_square01();
  shapes.push_back(&square01);

  glUseProgram(shaderProgram);
  int useOverrideColorLoc = glGetUniformLocation(shaderProgram, "useOverrideColor");
  int overrideColorLoc = glGetUniformLocation(shaderProgram, "overrideColor");

  while (!glfwWindowShouldClose(window)) {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto*& s : shapes) {
			glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), s->textures);
			s->bind_textures();
			glBindVertexArray(s->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, s->VBO);
			glBufferData(GL_ARRAY_BUFFER, s->vertices.size() * sizeof(float), s->vertices.data(), GL_STATIC_DRAW);
      glUniform1i(useOverrideColorLoc, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s->EBO_Triangles);
			glDrawElements(GL_TRIANGLES, s->indicesTriangles.size(), GL_UNSIGNED_INT, 0);	
    }
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    square01 *= moveRight;
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    square01 *= moveLeft;
  } 
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    square01 *= moveUp;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    square01 *= moveDown;
  }
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
  }
  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
  }
  if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
  }
  if (key == GLFW_KEY_Z && action == GLFW_PRESS) {  
    //cubo1.cubo.rotate_around_center(rotateZ);
    square01.pretty_transform(rotateZ);
  }
  if (key == GLFW_KEY_X && action == GLFW_PRESS) {
    //cubo1.cubo.rotate_around_center(rotateZ_);
    square01.pretty_transform(rotateZ_);
  }
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    //cubo1.cubo.scale_around_center(scaleUp);
    square01.pretty_transform(scaleUp);
  }
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    //cubo1.cubo.scale_around_center(scaleDown);
    square01.pretty_transform(scaleDown);
  }
  if (key == GLFW_KEY_O && action == GLFW_PRESS) {
    //cubo1.cubo *= moveRight;
    //cubo1.cubo.scale_around_center(scaleDown);
    //cubo1.cubo.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_L && action == GLFW_PRESS) {
    //cubo1.cubo *= moveDown;
    //cubo1.cubo.scale_around_center(scaleUp);
    //cubo1.cubo.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_K && action == GLFW_PRESS) {
    //cubo1.cubo *= moveLeft;
    //cubo1.cubo.scale_around_center(scaleDown);
    //cubo1.cubo.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_I && action == GLFW_PRESS) {
    //cubo1.cubo *= moveUp;
    //cubo1.cubo.scale_around_center(scaleUp);
    //cubo1.cubo.rotate_around_center(rotateZ);
  }
  square01.update_buffer();
}