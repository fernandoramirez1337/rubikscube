#pragma once

const char *vertexShaderSource =
	"#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
	"layout (location = 2) in vec2 aTexCoord;\n"
  "out vec3 ourColor;\n"
	"out vec2 TexCoord;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos, 1.0);\n"
  "   ourColor = aColor;\n"
	"	TexCoord = aTexCoord;\n"
  "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
  "in vec3 ourColor;\n"
  "in vec2 TexCoord;\n"
  "out vec4 FragColor;\n"
  "uniform sampler2D texture1;\n"
  "uniform bool useTexture;\n"
  "uniform bool useOverrideColor;\n"
  "uniform vec3 overrideColor;\n"
  "void main()\n"
  "{\n"
  "    if(useTexture) {\n"
  "        FragColor = texture(texture1, TexCoord);\n"		
  "    } else {\n"
  "        if(useOverrideColor) {\n"
  "            FragColor = vec4(overrideColor, 1.0);\n"
  "        } else {\n"
  "            FragColor = vec4(ourColor, 1.0);\n"
  "        }\n"
  "    }\n"
  "}\0";
;
