#include <vector>
#include <string>
#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;
#include "myshapes.hpp"

std::string get_out() {
  fs::path p = fs::current_path();
	int levels_path = 1;
	fs::path p_current; 
	p_current = p.parent_path();
	std::stringstream ss;
	ss << std::quoted( p_current.string() );
	std::string out;
	ss >> std::quoted(out);
  return out;
}

const translation moveRight(0.1f, 0.0f, 0.0f);
const translation moveLeft(-0.1f, 0.0f, 0.0f);
const translation moveUp(0.0f, 0.1f, 0.0f);
const translation moveDown(0.0f, -0.1f, 0.0f);
const scale scaleDown(0.90f, 0.90f, 1.0f);
const scale scaleUp(1.1f, 1.1f, 1.0f);
const rotate_z rotateZ(0.1f);
const rotate_z rotateZ_(-0.1f);

// 0 lines 1 triangles 1 textures
shape square01(0,1,1);
void build_square01() {
  /*
  square01.vertices = {
     0.2222f, -0.1778f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.2222f, -0.6222f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.2222f, -0.6222f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.2222f, -0.1778f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };
  */

  square01.vertices = {
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5,  -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };
  
  square01.indicesTriangles = {
    0, 1, 3,
    1, 2, 3
  };

  std::string img_path = get_out() + "/learnopengl/container.jpg";
  square01.load_txt(img_path.c_str());
  square01.build();
}

