#pragma once
#include <glm/glm.hpp>
#include "../core/component.hpp"

class DirectionalLight {
public:
    DirectionalLight();

    glm::vec3 direction;

    float intensity;
    glm::vec3 color;
};
