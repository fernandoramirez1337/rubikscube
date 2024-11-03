#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "workshop.cpp"
#include "rubiks.hpp"
#include "myshaders.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 920;

bool texxx = 1;

float d_test01 = 0.05;
cube test01(point( 0.5f, 0.5f,0.0f),d_test01,0,0,0,0,0,0,0);
cube test02(point(-0.5f, 0.5f,0.0f),d_test01,1,0,0,0,0,0,0);
cube test03(point( 0.5f,-0.5f,0.0f),d_test01,2,0,0,0,0,0,0);
cube test04(point(-0.5f,-0.5f,0.0f),d_test01);
rubiks test00(point(0,0,0),0.2,0);

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

  glEnable(GL_DEPTH_TEST);
  
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

  test00.build();
  test01.load_txt("../learnopengl/atlas.jpg");
  test01.bind_textures();
  test01.build();
  test02.load_txt("../learnopengl/atlas.jpg");
  test02.bind_textures();
  test02.build();
  test03.load_txt("../learnopengl/atlas.jpg");
  test03.bind_textures();
  test03.build();
  test04.build();

  shapes.push_back(&test01);
  shapes.push_back(&test02);
  shapes.push_back(&test03);
  shapes.push_back(&test04);

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
    for (auto& s : test00.pieces) {
      if (texxx) {
        glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), s->textures);
			  s->bind_textures();
      }
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
    test01 *= moveRight;
    test02 *= moveRight;
    test03 *= moveRight;
    test04 *= moveRight;
    test00.pretty_transform(moveRight);
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    test01 *= moveLeft;
    test02 *= moveLeft;
    test03 *= moveLeft;
    test04 *= moveLeft;
    test00.pretty_transform(moveLeft);
  } 
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    test01 *= moveUp;
    test02 *= moveUp;
    test03 *= moveUp;
    test04 *= moveUp;
    test00.pretty_transform(moveUp);
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    test01 *= moveDown;
    test02 *= moveDown;
    test03 *= moveDown;
    test04 *= moveDown;
    test00.pretty_transform(moveDown);
  }
  if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    test01 *= moveBack;
    test02 *= moveBack;
    test03 *= moveBack;
    test04 *= moveBack;
    test00.pretty_transform(moveBack);
  }
  if (key == GLFW_KEY_F && action == GLFW_PRESS) {
    test01 *= moveFront;
    test02 *= moveFront;
    test03 *= moveFront;
    test04 *= moveFront;
    test00.pretty_transform(moveFront);
  }
  if (key == GLFW_KEY_Z && action == GLFW_PRESS) {  
    test01.pretty_transform(rotateZ);
    test02.pretty_transform(rotateZ);
    test03.pretty_transform(rotateZ);
    test04.pretty_transform(rotateZ);
    test00.pretty_transform(rotateZ);
  }
  if (key == GLFW_KEY_X && action == GLFW_PRESS) {
    test01.pretty_transform(rotateZ_);
    test02.pretty_transform(rotateZ_);
    test03.pretty_transform(rotateZ_);
    test04.pretty_transform(rotateZ_);
    test00.pretty_transform(rotateZ_);
  }
  if (key == GLFW_KEY_C && action == GLFW_PRESS) {  
    test01.pretty_transform(rotateY);
    test02.pretty_transform(rotateY);
    test03.pretty_transform(rotateY);
    test04.pretty_transform(rotateY);
    test00.pretty_transform(rotateY);
  }
  if (key == GLFW_KEY_V && action == GLFW_PRESS) {
    test01.pretty_transform(rotateY_);
    test02.pretty_transform(rotateY_);
    test03.pretty_transform(rotateY_);
    test04.pretty_transform(rotateY_);
    test00.pretty_transform(rotateY_);
  }
  if (key == GLFW_KEY_B && action == GLFW_PRESS) {  
    test01.pretty_transform(rotateX);
    test02.pretty_transform(rotateX);
    test03.pretty_transform(rotateX);
    test04.pretty_transform(rotateX);
    test00.pretty_transform(rotateX);
  }
  if (key == GLFW_KEY_N && action == GLFW_PRESS) {
    test01.pretty_transform(rotateX_);
    test02.pretty_transform(rotateX_);
    test03.pretty_transform(rotateX_);
    test04.pretty_transform(rotateX_);
    test00.pretty_transform(rotateX_);
  }
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    test01.pretty_transform(scaleUp);
    test02.pretty_transform(scaleUp);
    test03.pretty_transform(scaleUp);
    test04.pretty_transform(scaleUp);
    test00.pretty_transform(scaleUp);
  }
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    test01.pretty_transform(scaleDown);
    test02.pretty_transform(scaleDown);
    test03.pretty_transform(scaleDown);
    test04.pretty_transform(scaleDown);
    test00.pretty_transform(scaleDown);
  }
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    texxx = !texxx;
  }
  test01.update_buffer();
  test02.update_buffer();
  test03.update_buffer();
  test04.update_buffer();
  test00.update_buffer();
}