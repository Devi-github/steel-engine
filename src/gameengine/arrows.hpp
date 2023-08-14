#pragma once

#include <glm/glm.hpp>

class IArrow {
public:
    virtual void draw(glm::vec3 position) = 0;
};

void setup_arrows();

void draw_move_arrows(glm::vec3 position);
void draw_scale_arrows(glm::vec3 position);
void draw_rotate_sphere(glm::vec3 position);
