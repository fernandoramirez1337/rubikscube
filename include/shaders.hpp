#ifndef SHADERS_HPP
#define SHADERS_HPP

const char *vertexShader1Source = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";
  //orange
const char *fragmentShader1Source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
  "}\n\0";
  //yellow
const char *fragmentShader2Source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
  "}\n\0";

const char *fragmentShader3Source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
  "}\n\0";
const char *fragmentShader4Source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
  "}\n\0";
const char *fragmentShader5Source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
  "}\n\0";

struct ShaderProgram {
  unsigned int id;
  unsigned int vertexShader;
  unsigned int fragmentShader;
};

ShaderProgram createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource) {
  ShaderProgram program;
  program.vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(program.vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(program.vertexShader);
  program.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(program.fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(program.fragmentShader);
  return program;
}
#endif