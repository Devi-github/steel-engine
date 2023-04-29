#pragma once
#include <glm/glm.hpp>
#include "../component.hpp"

class Transform : public BaseComponent {
public:
    Transform();

    glm::vec3 position;
    glm::vec3 rotation; // Euler angles
};