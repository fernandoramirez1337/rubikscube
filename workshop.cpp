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
const translation moveFront(0.0f, 0.0f, -0.1f);
const translation moveBack(0.0f, 0.0f, 0.1f);
const scale scaleDown(0.90f, 0.90f, 0.9f);
const scale scaleUp(1.1f, 1.1f, 1.1f);
const rotate_z rotateZ(0.1f);
const rotate_z_inv rotateZ_(0.1f);
const rotate_y rotateY(0.1f);
const rotate_y_inv rotateY_(0.1f);
const rotate_x rotateX(0.1f);
const rotate_x_inv rotateX_(0.1f);

/*
// 0 lines 1 triangles 1 textures
shape square01(0,1,0);
void build_square01() {
  square01.vertices = {
     0.2222f, -0.1778f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.2222f, -0.6222f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.2222f, -0.6222f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.2222f, -0.1778f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };

// Verde RGB(0, 155, 72)
float verde_r = 0.0f / 255.0f;
float verde_g = 155.0f / 255.0f;
float verde_b = 72.0f / 255.0f;

// Blanco RGB(255, 255, 255)
float blanco_r = 255.0f / 255.0f;
float blanco_g = 255.0f / 255.0f;
float blanco_b = 255.0f / 255.0f;

// Rojo RGB(183, 18, 52)
float rojo_r = 183.0f / 255.0f;
float rojo_g = 18.0f / 255.0f;
float rojo_b = 52.0f / 255.0f;

// Amarillo RGB(255, 223, 0)
float amarillo_r = 255.0f / 255.0f;
float amarillo_g = 223.0f / 255.0f;
float amarillo_b = 0.0f / 255.0f;

// Azul RGB(0, 70, 173)
float azul_r = 0.0f / 255.0f;
float azul_g = 70.0f / 255.0f;
float azul_b = 173.0f / 255.0f;

// Naranja RGB(255, 88, 0)
float naranja_r = 255.0f / 255.0f;
float naranja_g = 88.0f / 255.0f;
float naranja_b = 0.0f / 255.0f;


  square01.vertices = {
    // back
     0.5f,  0.5f, 0.5f, naranja_r, naranja_g, naranja_b, 1.0f, 1.0f,
     0.5f, -0.5f, 0.5f, naranja_r, naranja_g, naranja_b, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, naranja_r, naranja_g, naranja_b, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.5f, naranja_r, naranja_g, naranja_b, 0.0f, 1.0f,

    // front
     0.5f,  0.5f, -0.5f, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,

    // down
     0.5f, -0.5f,  0.5f, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,


    // up 
     0.5f,  0.5f,  0.5f, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,

    // left
    -0.5f,  0.5f,  0.5f, azul_r, azul_g, azul_b, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, azul_r, azul_g, azul_b, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, azul_r, azul_g, azul_b, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, azul_r, azul_g, azul_b, 0.0f, 0.0f,

    // right
     0.5f,  0.5f,  0.5f, verde_r, verde_g, verde_b, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, verde_r, verde_g, verde_b, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, verde_r, verde_g, verde_b, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, verde_r, verde_g, verde_b, 0.0f, 0.0f
};
  
  square01.indicesTriangles = {
    0, 1, 3,
    1, 2, 3,

    4, 5, 7,
    5, 6, 7,

    8, 9, 11,
    9, 10, 11,

    12, 13, 15,
    13, 14, 15,

    16, 17, 19,
    17, 18, 19,
    
    20, 21, 23,
    21, 22, 23    
  };

  std::string img_path = get_out() + "/learnopengl/container.jpg";
  square01.load_txt(img_path.c_str());
  square01.build();
}
*/
