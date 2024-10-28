#include "rubiks.hpp"

const float verde_r = 0.0f / 255.0f;
const float verde_g = 155.0f / 255.0f;
const float verde_b = 72.0f / 255.0f;

// Blanco RGB(255, 255, 255)
const float blanco_r = 255.0f / 255.0f;
const float blanco_g = 255.0f / 255.0f;
const float blanco_b = 255.0f / 255.0f;

// Rojo RGB(183, 18, 52)
const float rojo_r = 183.0f / 255.0f;
const float rojo_g = 18.0f / 255.0f;
const float rojo_b = 52.0f / 255.0f;

// Amarillo RGB(255, 223, 0)
const float amarillo_r = 255.0f / 255.0f;
const float amarillo_g = 223.0f / 255.0f;
const float amarillo_b = 0.0f / 255.0f;

// Azul RGB(0, 70, 173)
const float azul_r = 0.0f / 255.0f;
const float azul_g = 70.0f / 255.0f;
const float azul_b = 173.0f / 255.0f;

// Naranja RGB(255, 88, 0)
const float naranja_r = 255.0f / 255.0f;
const float naranja_g = 88.0f / 255.0f;
const float naranja_b = 0.0f / 255.0f;

cube::cube(const point& c, float d) : shape(0,1,0) {
  const float cx_minus_d = c.x - d;
  const float cx_plus_d = c.x + d;
  const float cy_minus_d = c.y - d;
  const float cy_plus_d = c.y + d;
  const float cz_minus_d = c.z - d;
  const float cz_plus_d = c.z + d;

 vertices = {
    // Back face (naranja)
    cx_plus_d, cy_plus_d, cz_plus_d, naranja_r, naranja_g, naranja_b, 0.0f, 0.0f,
    cx_plus_d, cy_minus_d, cz_plus_d, naranja_r, naranja_g, naranja_b, 0.0f, 0.0f,
    cx_minus_d, cy_minus_d, cz_plus_d, naranja_r, naranja_g, naranja_b, 0.0f, 0.0f,
    cx_minus_d, cy_plus_d, cz_plus_d, naranja_r, naranja_g, naranja_b, 0.0f, 0.0f,

    // Front face (rojo)
    cx_plus_d, cy_plus_d, cz_minus_d, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,
    cx_plus_d, cy_minus_d, cz_minus_d, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,
    cx_minus_d, cy_minus_d, cz_minus_d, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,
    cx_minus_d, cy_plus_d, cz_minus_d, rojo_r, rojo_g, rojo_b, 0.0f, 0.0f,

    // Bottom face (blanco)
    cx_plus_d, cy_minus_d, cz_plus_d, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,
    cx_plus_d, cy_minus_d, cz_minus_d, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,
    cx_minus_d, cy_minus_d, cz_minus_d, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,
    cx_minus_d, cy_minus_d, cz_plus_d, blanco_r, blanco_g, blanco_b, 0.0f, 0.0f,

    // Top face (amarillo)
    cx_plus_d, cy_plus_d, cz_plus_d, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,
    cx_plus_d, cy_plus_d, cz_minus_d, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,
    cx_minus_d, cy_plus_d, cz_minus_d, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,
    cx_minus_d, cy_plus_d, cz_plus_d, amarillo_r, amarillo_g, amarillo_b, 0.0f, 0.0f,

    // Left face (azul)
    cx_minus_d, cy_plus_d, cz_plus_d, azul_r, azul_g, azul_b, 0.0f, 0.0f,
    cx_minus_d, cy_plus_d, cz_minus_d, azul_r, azul_g, azul_b, 0.0f, 0.0f,
    cx_minus_d, cy_minus_d, cz_minus_d, azul_r, azul_g, azul_b, 0.0f, 0.0f,
    cx_minus_d, cy_minus_d, cz_plus_d, azul_r, azul_g, azul_b, 0.0f, 0.0f,

    // Right face (verde)
    cx_plus_d, cy_plus_d, cz_plus_d, verde_r, verde_g, verde_b, 0.0f, 0.0f,
    cx_plus_d, cy_plus_d, cz_minus_d, verde_r, verde_g, verde_b, 0.0f, 0.0f,
    cx_plus_d, cy_minus_d, cz_minus_d, verde_r, verde_g, verde_b, 0.0f, 0.0f,
    cx_plus_d, cy_minus_d, cz_plus_d, verde_r, verde_g, verde_b, 0.0f, 0.0f
  };

  indicesTriangles = {
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
};

rubiks::rubiks(const point &c, float d) : pieces{} {
  const float core_x = c.x;
  const float core_y = c.y;
  const float core_z = c.z;
  const float mini_d = d / 2.1f;

  // Corner pieces (8)
  pieces[0] = std::make_unique<cube>(point(core_x - d, core_y - d, core_z - d), mini_d);
  pieces[1] = std::make_unique<cube>(point(core_x - d, core_y - d, core_z + d), mini_d);
  pieces[2] = std::make_unique<cube>(point(core_x - d, core_y + d, core_z - d), mini_d);
  pieces[3] = std::make_unique<cube>(point(core_x - d, core_y + d, core_z + d), mini_d);
  pieces[4] = std::make_unique<cube>(point(core_x + d, core_y - d, core_z - d), mini_d);
  pieces[5] = std::make_unique<cube>(point(core_x + d, core_y - d, core_z + d), mini_d);
  pieces[6] = std::make_unique<cube>(point(core_x + d, core_y + d, core_z - d), mini_d);
  pieces[7] = std::make_unique<cube>(point(core_x + d, core_y + d, core_z + d), mini_d);

  // Edge pieces (12)
  pieces[8]  = std::make_unique<cube>(point(core_x - d, core_y, core_z - d), mini_d);
  pieces[9]  = std::make_unique<cube>(point(core_x - d, core_y, core_z + d), mini_d);
  pieces[10] = std::make_unique<cube>(point(core_x, core_y - d, core_z - d), mini_d);
  pieces[11] = std::make_unique<cube>(point(core_x, core_y - d, core_z + d), mini_d);
  pieces[12] = std::make_unique<cube>(point(core_x + d, core_y, core_z - d), mini_d);
  pieces[13] = std::make_unique<cube>(point(core_x + d, core_y, core_z + d), mini_d);
  pieces[14] = std::make_unique<cube>(point(core_x, core_y + d, core_z - d), mini_d);
  pieces[15] = std::make_unique<cube>(point(core_x, core_y + d, core_z + d), mini_d);
  pieces[16] = std::make_unique<cube>(point(core_x - d, core_y - d, core_z), mini_d);
  pieces[17] = std::make_unique<cube>(point(core_x - d, core_y + d, core_z), mini_d);
  pieces[18] = std::make_unique<cube>(point(core_x + d, core_y - d, core_z), mini_d);
  pieces[19] = std::make_unique<cube>(point(core_x + d, core_y + d, core_z), mini_d);

  // Center pieces (6)
  pieces[20] = std::make_unique<cube>(point(core_x - d, core_y, core_z), mini_d); // Left face center
  pieces[21] = std::make_unique<cube>(point(core_x + d, core_y, core_z), mini_d); // Right face center
  pieces[22] = std::make_unique<cube>(point(core_x, core_y - d, core_z), mini_d); // Bottom face center
  pieces[23] = std::make_unique<cube>(point(core_x, core_y + d, core_z), mini_d); // Top face center
  pieces[24] = std::make_unique<cube>(point(core_x, core_y, core_z - d), mini_d); // Front face center
  pieces[25] = std::make_unique<cube>(point(core_x, core_y, core_z + d), mini_d); // Back face center
}

void rubiks::build() {
  for (auto& p : pieces) {
    p.get()->build();
  }
}

void rubiks::update_buffer() {
  for (auto& p : pieces) {
    p.get()->update_buffer();
  }
}

void rubiks::pretty_transform(const matrix& m) {
  point curr = center;
  center = translation_inv(curr.x, curr.y, curr.z) * center;
  center = m * center;
  center = translation(curr.x, curr.y, curr.z) * center;
  for (auto& p : pieces) {
    p.get()->transform_around(m, center);
  }
}
