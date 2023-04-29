#pragma once
#include <glm/glm.hpp>
#include "../component.hpp"

class Transform : public BaseComponent {
public:
    Transform();

    glm::mat4 modelMatrix();

    void rotate(glm::vec3 euler);
    glm::vec3 forward();
    glm::vec3 right();
    glm::vec3 up();

    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0); // Euler angles
    glm::vec3 scale = glm::vec3(1);
};