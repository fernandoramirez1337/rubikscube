#include "rubiks.hpp"

const float ver_r = 0.0f / 255.0f;
const float ver_g = 155.0f / 255.0f;
const float ver_b = 72.0f / 255.0f;

// Blanco RGB(255, 255, 255)
const float bla_r = 255.0f / 255.0f;
const float bla_g = 255.0f / 255.0f;
const float bla_b = 255.0f / 255.0f;

// Rojo RGB(183, 18, 52)
const float roj_r = 183.0f / 255.0f;
const float roj_g = 18.0f / 255.0f;
const float roj_b = 52.0f / 255.0f;

// Amarillo RGB(255, 223, 0)
const float ama_r = 255.0f / 255.0f;
const float ama_g = 223.0f / 255.0f;
const float ama_b = 0.0f / 255.0f;

// Azul RGB(0, 70, 173)
const float azu_r = 0.0f / 255.0f;
const float azu_g = 70.0f / 255.0f;
const float azu_b = 173.0f / 255.0f;

// Naranja RGB(255, 88, 0)
const float nar_r = 255.0f / 255.0f;
const float nar_g = 88.0f / 255.0f;
const float nar_b = 0.0f / 255.0f;

cube::cube(const point& c, float d) : shape(0,1,0) {
  const float cx_m_d = c.x - d;
  const float cx_p_d = c.x + d;
  const float cy_m_d = c.y - d;
  const float cy_p_d = c.y + d;
  const float cz_m_d = c.z - d;
  const float cz_p_d = c.z + d;

 vertices = {
    // Back face (naranja)
    cx_p_d, cy_p_d, cz_p_d, nar_r, nar_g, nar_b, 0.0f, 0.0f,
    cx_p_d, cy_m_d, cz_p_d, nar_r, nar_g, nar_b, 0.0f, 0.0f,
    cx_m_d, cy_m_d, cz_p_d, nar_r, nar_g, nar_b, 0.0f, 0.0f,
    cx_m_d, cy_p_d, cz_p_d, nar_r, nar_g, nar_b, 0.0f, 0.0f,

    // Front face (rojo)
    cx_p_d, cy_p_d, cz_m_d, roj_r, roj_g, roj_b, 0.0f, 0.0f,
    cx_p_d, cy_m_d, cz_m_d, roj_r, roj_g, roj_b, 0.0f, 0.0f,
    cx_m_d, cy_m_d, cz_m_d, roj_r, roj_g, roj_b, 0.0f, 0.0f,
    cx_m_d, cy_p_d, cz_m_d, roj_r, roj_g, roj_b, 0.0f, 0.0f,

    // Bottom face (blanco)
    cx_p_d, cy_m_d, cz_p_d, bla_r, bla_g, bla_b, 0.0f, 0.0f,
    cx_p_d, cy_m_d, cz_m_d, bla_r, bla_g, bla_b, 0.0f, 0.0f,
    cx_m_d, cy_m_d, cz_m_d, bla_r, bla_g, bla_b, 0.0f, 0.0f,
    cx_m_d, cy_m_d, cz_p_d, bla_r, bla_g, bla_b, 0.0f, 0.0f,

    // Top face (amarillo)
    cx_p_d, cy_p_d, cz_p_d, ama_r, ama_g, ama_b, 0.0f, 0.0f,
    cx_p_d, cy_p_d, cz_m_d, ama_r, ama_g, ama_b, 0.0f, 0.0f,
    cx_m_d, cy_p_d, cz_m_d, ama_r, ama_g, ama_b, 0.0f, 0.0f,
    cx_m_d, cy_p_d, cz_p_d, ama_r, ama_g, ama_b, 0.0f, 0.0f,

    // Left face (azul)
    cx_m_d, cy_p_d, cz_p_d, azu_r, azu_g, azu_b, 0.0f, 0.0f,
    cx_m_d, cy_p_d, cz_m_d, azu_r, azu_g, azu_b, 0.0f, 0.0f,
    cx_m_d, cy_m_d, cz_m_d, azu_r, azu_g, azu_b, 0.0f, 0.0f,
    cx_m_d, cy_m_d, cz_p_d, azu_r, azu_g, azu_b, 0.0f, 0.0f,

    // Right face (verde)
    cx_p_d, cy_p_d, cz_p_d, ver_r, ver_g, ver_b, 0.0f, 0.0f,
    cx_p_d, cy_p_d, cz_m_d, ver_r, ver_g, ver_b, 0.0f, 0.0f,
    cx_p_d, cy_m_d, cz_m_d, ver_r, ver_g, ver_b, 0.0f, 0.0f,
    cx_p_d, cy_m_d, cz_p_d, ver_r, ver_g, ver_b, 0.0f, 0.0f
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
}

cube::cube(const point& c, float d_, unsigned int texture_id, bool back, bool front, bool down, bool up, bool left, bool right) : shape(0,1,1) {
  const float cx = c.x, cy = c.y, cz = c.z, d = d_;
  const float cx_m_d = cx - d, cx_p_d = cx + d, 
              cy_m_d = cy - d, cy_p_d = cy + d, 
              cz_m_d = cz - d, cz_p_d = cz + d;
  if (texture_id > 4) texture_id = 0;
  const float atlas = 1.0f / 7.0f, l = 0.0f, r = 1.0f, t = 1.0f, b = 0.0f, ty = texture_id;
  float t0_x = 5, t0_y = ty,
        t1_x = 2, t1_y = ty,
        t2_x = 1, t2_y = ty,
        t3_x = 3, t3_y = ty,
        t4_x = 4, t4_y = ty,
        t5_x = 0, t5_y = ty;
  // all white (6,2) all black (6,6)
  if (texture_id == 1) {
    if (back) { t0_x = 6, t0_y = 2; }
    if (front){ t1_x = 6, t1_y = 2; }
    if (down) { t2_x = 6, t2_y = 2; }
    if (up)   { t3_x = 6, t3_y = 2; }
    if (left) { t4_x = 6, t4_y = 2; }
    if (right){ t5_x = 6, t5_y = 2; }
  } else {
    if (back) { t0_x = 6, t0_y = 6; }
    if (front){ t1_x = 6, t1_y = 6; }
    if (down) { t2_x = 6, t2_y = 6; }
    if (up)   { t3_x = 6, t3_y = 6; }
    if (left) { t4_x = 6, t4_y = 6; }
    if (right){ t5_x = 6, t5_y = 6; }
  }
  

  vertices = {
      // Back face (orange)
    cx_p_d, cy_p_d, cz_p_d, nar_r, nar_g, nar_b, (t0_x + l) * atlas, (t0_y + t) * atlas,
    cx_p_d, cy_m_d, cz_p_d, nar_r, nar_g, nar_b, (t0_x + r) * atlas, (t0_y + t) * atlas,
    cx_m_d, cy_m_d, cz_p_d, nar_r, nar_g, nar_b, (t0_x + r) * atlas, (t0_y + b) * atlas,
    cx_m_d, cy_p_d, cz_p_d, nar_r, nar_g, nar_b, (t0_x + l) * atlas, (t0_y + b) * atlas,

    // Front face (red)
    cx_p_d, cy_p_d, cz_m_d, roj_r, roj_g, roj_b, (t1_x + l) * atlas, (t1_y + t) * atlas,
    cx_p_d, cy_m_d, cz_m_d, roj_r, roj_g, roj_b, (t1_x + r) * atlas, (t1_y + t) * atlas,
    cx_m_d, cy_m_d, cz_m_d, roj_r, roj_g, roj_b, (t1_x + r) * atlas, (t1_y + b) * atlas,
    cx_m_d, cy_p_d, cz_m_d, roj_r, roj_g, roj_b, (t1_x + l) * atlas, (t1_y + b) * atlas,

    // Bottom face (white)
    cx_p_d, cy_m_d, cz_p_d, bla_r, bla_g, bla_b, (t2_x + l) * atlas, (t2_y + b) * atlas,
    cx_p_d, cy_m_d, cz_m_d, bla_r, bla_g, bla_b, (t2_x + r) * atlas, (t2_y + b) * atlas,
    cx_m_d, cy_m_d, cz_m_d, bla_r, bla_g, bla_b, (t2_x + r) * atlas, (t2_y + t) * atlas,
    cx_m_d, cy_m_d, cz_p_d, bla_r, bla_g, bla_b, (t2_x + l) * atlas, (t2_y + t) * atlas,

    // Top face (yellow)
    cx_p_d, cy_p_d, cz_p_d, ama_r, ama_g, ama_b, (t3_x + l) * atlas, (t3_y + t) * atlas,
    cx_p_d, cy_p_d, cz_m_d, ama_r, ama_g, ama_b, (t3_x + r) * atlas, (t3_y + t) * atlas,
    cx_m_d, cy_p_d, cz_m_d, ama_r, ama_g, ama_b, (t3_x + r) * atlas, (t3_y + b) * atlas,
    cx_m_d, cy_p_d, cz_p_d, ama_r, ama_g, ama_b, (t3_x + l) * atlas, (t3_y + b) * atlas,

    // Left face (blue)
    cx_m_d, cy_p_d, cz_p_d, azu_r, azu_g, azu_b, (t4_x + l) * atlas, (t4_y + t) * atlas,
    cx_m_d, cy_p_d, cz_m_d, azu_r, azu_g, azu_b, (t4_x + r) * atlas, (t4_y + t) * atlas,
    cx_m_d, cy_m_d, cz_m_d, azu_r, azu_g, azu_b, (t4_x + r) * atlas, (t4_y + b) * atlas,
    cx_m_d, cy_m_d, cz_p_d, azu_r, azu_g, azu_b, (t4_x + l) * atlas, (t4_y + b) * atlas,

    // Right face (green)
    cx_p_d, cy_p_d, cz_p_d, ver_r, ver_g, ver_b, (t5_x + l) * atlas, (t5_y + t) * atlas,
    cx_p_d, cy_p_d, cz_m_d, ver_r, ver_g, ver_b, (t5_x + r) * atlas, (t5_y + t) * atlas,
    cx_p_d, cy_m_d, cz_m_d, ver_r, ver_g, ver_b, (t5_x + r) * atlas, (t5_y + b) * atlas,
    cx_p_d, cy_m_d, cz_p_d, ver_r, ver_g, ver_b, (t5_x + l) * atlas, (t5_y + b) * atlas
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
  if (texture_id == 0)
  if (back && front && left && right && up && !down) {
    vertices[64 + 6] = (6 + l) * atlas;
    vertices[64 + 7] = (0 + b) * atlas;

    vertices[72 + 6] = (6 + r) * atlas;
    vertices[72 + 7] = (0 + b) * atlas;

    vertices[80 + 6] = (6 + r) * atlas;
    vertices[80 + 7] = (0 + t) * atlas;

    vertices[88 + 6] = (6 + l) * atlas;
    vertices[88 + 7] = (0 + t) * atlas;
  }
}

rubiks::rubiks(const point &c, float d, unsigned int t_id) : pieces{} {
  const float core_x = c.x;
  const float core_y = c.y;
  const float core_z = c.z;
  const float mini_d = d / 3.1f;
  const float texture_id = t_id;

  // naranja rojo blanco amarillo azul verde
  // Corner pieces (8)
  pieces[0] = std::make_unique<cube>(point(core_x - d, core_y - d, core_z - d), mini_d,t_id,1,0,0,1,0,1); 
  pieces[1] = std::make_unique<cube>(point(core_x - d, core_y - d, core_z + d), mini_d,t_id,0,1,0,1,0,1);
  pieces[2] = std::make_unique<cube>(point(core_x - d, core_y + d, core_z - d), mini_d,t_id,1,0,1,0,0,1);
  pieces[3] = std::make_unique<cube>(point(core_x - d, core_y + d, core_z + d), mini_d,t_id,0,1,1,0,0,1);
  pieces[4] = std::make_unique<cube>(point(core_x + d, core_y - d, core_z - d), mini_d,t_id,1,0,0,1,1,0);
  pieces[5] = std::make_unique<cube>(point(core_x + d, core_y - d, core_z + d), mini_d,t_id,0,1,0,1,1,0);
  pieces[6] = std::make_unique<cube>(point(core_x + d, core_y + d, core_z - d), mini_d,t_id,1,0,1,0,1,0);
  pieces[7] = std::make_unique<cube>(point(core_x + d, core_y + d, core_z + d), mini_d,t_id,0,1,1,0,1,0);

  // Edge pieces (12)
  pieces[8]  = std::make_unique<cube>(point(core_x - d, core_y, core_z - d), mini_d,t_id,1,0,1,1,0,1);
  pieces[9]  = std::make_unique<cube>(point(core_x - d, core_y, core_z + d), mini_d,t_id,0,1,1,1,0,1);
  pieces[10] = std::make_unique<cube>(point(core_x, core_y - d, core_z - d), mini_d,t_id,1,0,0,1,1,1);
  pieces[11] = std::make_unique<cube>(point(core_x, core_y - d, core_z + d), mini_d,t_id,0,1,0,1,1,1);
  pieces[12] = std::make_unique<cube>(point(core_x + d, core_y, core_z - d), mini_d,t_id,1,0,1,1,1,0);
  pieces[13] = std::make_unique<cube>(point(core_x + d, core_y, core_z + d), mini_d,t_id,0,1,1,1,1,0);
  pieces[14] = std::make_unique<cube>(point(core_x, core_y + d, core_z - d), mini_d,t_id,1,0,1,0,1,1);
  pieces[15] = std::make_unique<cube>(point(core_x, core_y + d, core_z + d), mini_d,t_id,0,1,1,0,1,1);
  pieces[16] = std::make_unique<cube>(point(core_x - d, core_y - d, core_z), mini_d,t_id,1,1,0,1,0,1);
  pieces[17] = std::make_unique<cube>(point(core_x - d, core_y + d, core_z), mini_d,t_id,1,1,1,0,0,1);
  pieces[18] = std::make_unique<cube>(point(core_x + d, core_y - d, core_z), mini_d,t_id,1,1,0,1,1,0);
  pieces[19] = std::make_unique<cube>(point(core_x + d, core_y + d, core_z), mini_d,t_id,1,1,1,0,1,0);

  // Center pieces (6)
  pieces[20] = std::make_unique<cube>(point(core_x + d, core_y, core_z), mini_d,t_id,1,1,1,1,1,0); // Right face center
  pieces[21] = std::make_unique<cube>(point(core_x - d, core_y, core_z), mini_d,t_id,1,1,1,1,0,1); // Left face center
  pieces[22] = std::make_unique<cube>(point(core_x, core_y + d, core_z), mini_d,t_id,1,1,1,0,1,1); // Top face center
  pieces[23] = std::make_unique<cube>(point(core_x, core_y - d, core_z), mini_d,t_id,1,1,0,1,1,1); // Bottom face center
  pieces[24] = std::make_unique<cube>(point(core_x, core_y, core_z - d), mini_d,t_id,1,0,1,1,1,1); // Front face center
  pieces[25] = std::make_unique<cube>(point(core_x, core_y, core_z + d), mini_d,t_id,0,1,1,1,1,1); // Back face center
}

void rubiks::build() {
  for (auto& p : pieces) {
    p.get()->load_txt("../learnopengl/atlas.jpg");
    p.get()->bind_textures();
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
