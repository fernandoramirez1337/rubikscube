#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "mylib.hpp"
#include "shaders.hpp"
#include "myshapes.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 732;
unsigned int renderMode = GL_LINES;

std::array<ShaderProgram, 5> shaderPrograms;

int main() {
  //create_testShape();
  create_pizza1();
  
  // GLFW initialization and configuration
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  // Window creation
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  // GLAD initialization
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  shaderPrograms = createAllShaderPrograms();

  pizza1.setup_gl();

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    pizza1.sub_data_gl();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pizza1.draw_gl(renderMode, shaderPrograms);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for (auto& program : shaderPrograms) {
    glDeleteShader(program.vertexShader);
    glDeleteShader(program.fragmentShader);
    glDeleteProgram(program.id);
  }

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
    pizza1 *= moveRight;
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    pizza1 *= moveLeft;
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    pizza1 *= moveUp;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    pizza1 *= moveDown;
  }
  if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
    renderMode = GL_TRIANGLES;
  }
  if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
    renderMode = GL_LINES;
  }
  if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
    renderMode = GL_POINTS;
  }
  if (key == GLFW_KEY_Z && action == GLFW_PRESS) {  
    pizza1.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_X && action == GLFW_PRESS) {
    pizza1.rotate_around_center(rotateZ_);
  }
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    pizza1.scale_around_center(scaleUp);
  }
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    pizza1.scale_around_center(scaleDown);
  }
  if (key == GLFW_KEY_O && action == GLFW_PRESS) {
    pizza1 *= moveRight;
    pizza1.scale_around_center(scaleDown);
    pizza1.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_L && action == GLFW_PRESS) {
    pizza1 *= moveDown;
    pizza1.scale_around_center(scaleUp);
    pizza1.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_K && action == GLFW_PRESS) {
    pizza1 *= moveLeft;
    pizza1.scale_around_center(scaleDown);
    pizza1.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_I && action == GLFW_PRESS) {
    pizza1 *= moveUp;
    pizza1.scale_around_center(scaleUp);
    pizza1.rotate_around_center(rotateZ);
  }
}