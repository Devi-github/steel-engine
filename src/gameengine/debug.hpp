#pragma once

#include <glm/glm.hpp>

void setup_debug();

glm::vec3 current_color();
void set_debug_color(glm::vec3 col);
void draw_line(glm::vec3 p1, glm::vec3 p2);
void draw_wire_cube(glm::vec3 cpos, glm::vec3 scaling);
