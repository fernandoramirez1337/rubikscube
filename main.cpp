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

int main() {
  create_testShape();

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShader1Source, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShaderWhite = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderWhite, 1, &fragmentShader1Source, NULL);
  glCompileShader(fragmentShaderWhite);

  unsigned int fragmentShaderBlack = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderBlack, 1, &fragmentShader2Source, NULL);
  glCompileShader(fragmentShaderBlack);

  unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderRed, 1, &fragmentShader3Source, NULL);
  glCompileShader(fragmentShaderRed);

  unsigned int fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderGreen, 1, &fragmentShader4Source, NULL);
  glCompileShader(fragmentShaderGreen);

  unsigned int fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderBlue, 1, &fragmentShader5Source, NULL);
  glCompileShader(fragmentShaderBlue);

  unsigned int shaderProgramWhite = glCreateProgram();
  glAttachShader(shaderProgramWhite, vertexShader);
  glAttachShader(shaderProgramWhite, fragmentShaderWhite);
  glLinkProgram(shaderProgramWhite);

  unsigned int shaderProgramBlack = glCreateProgram();
  glAttachShader(shaderProgramBlack, vertexShader);
  glAttachShader(shaderProgramBlack, fragmentShaderBlack);
  glLinkProgram(shaderProgramBlack);

  unsigned int shaderProgramRed = glCreateProgram();
  glAttachShader(shaderProgramRed, vertexShader);
  glAttachShader(shaderProgramRed, fragmentShaderRed);
  glLinkProgram(shaderProgramRed);

  unsigned int shaderProgramGreen = glCreateProgram();
  glAttachShader(shaderProgramGreen, vertexShader);
  glAttachShader(shaderProgramGreen, fragmentShaderGreen);
  glLinkProgram(shaderProgramGreen);

  unsigned int shaderProgramBlue = glCreateProgram();
  glAttachShader(shaderProgramBlue, vertexShader);
  glAttachShader(shaderProgramBlue, fragmentShaderBlue);
  glLinkProgram(shaderProgramBlue);

  const size_t numberOfVertices = testShape.vertices.size() * 3;
  float vertices[numberOfVertices];
  testShape.get_vertices(vertices);

  const size_t numberOfIndices = testShape.indices[0].size();
  unsigned int indices[numberOfIndices];
  testShape.get_indices(indices);

  testShape.VAOs.resize(1);
  testShape.VBOs.resize(1);
  testShape.EBOs.resize(1);

  glGenVertexArrays(1, &testShape.VAOs[0]);
  glGenBuffers(1, &testShape.VBOs[0]);
  glGenBuffers(1, &testShape.EBOs[0]);

  glBindVertexArray(testShape.VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, testShape.VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(float), vertices, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testShape.EBOs[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    testShape.get_vertices(vertices);

    glBindBuffer(GL_ARRAY_BUFFER, testShape.VBOs[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, numberOfVertices * sizeof(float), vertices);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (renderMode == GL_LINES) {
      glUseProgram(shaderProgramGreen);
      glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
    } else if (renderMode == GL_TRIANGLES) {
      glUseProgram(shaderProgramWhite);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    } else if (renderMode == GL_POINTS) {
      glUseProgram(shaderProgramRed);
      glPointSize(10.0f);
      glDrawElements(GL_POINTS, 3, GL_UNSIGNED_INT, 0);
      glPointSize(1.0f);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, testShape.VAOs.data());
  glDeleteBuffers(1, testShape.VBOs.data());
  glDeleteBuffers(1, testShape.EBOs.data());

  glDeleteShader(vertexShader);

  glDeleteProgram(shaderProgramWhite);
  glDeleteProgram(shaderProgramBlack);
  glDeleteProgram(shaderProgramRed);
  glDeleteProgram(shaderProgramGreen);
  glDeleteProgram(shaderProgramBlue);

  glDeleteShader(fragmentShaderRed);
  glDeleteShader(fragmentShaderGreen);
  glDeleteShader(fragmentShaderBlue);
  glDeleteShader(fragmentShaderWhite);
  glDeleteShader(fragmentShaderBlack);
   
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
    testShape *= moveRight;
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    testShape *= moveLeft;
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    testShape *= moveUp;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    testShape *= moveDown;
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
    testShape.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_X && action == GLFW_PRESS) {
    testShape.rotate_around_center(rotateZ_);
  }
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    testShape.scale_around_center(scaleUp);
  }
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    testShape.scale_around_center(scaleDown);
  }
  if (key == GLFW_KEY_O && action == GLFW_PRESS) {
    testShape *= moveRight;
    testShape.scale_around_center(scaleDown);
    testShape.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_L && action == GLFW_PRESS) {
    testShape *= moveDown;
    testShape.scale_around_center(scaleUp);
    testShape.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_K && action == GLFW_PRESS) {
    testShape *= moveLeft;
    testShape.scale_around_center(scaleDown);
    testShape.rotate_around_center(rotateZ);
  }
  if (key == GLFW_KEY_I && action == GLFW_PRESS) {
    testShape *= moveUp;
    testShape.scale_around_center(scaleUp);
    testShape.rotate_around_center(rotateZ);
  }
}