#pragma once
#include <glm/glm.hpp>
#include "../component.hpp"

class Transform : public BaseComponent {
public:
    Transform();
    Transform(const Transform& other);

    void copyTransform(Transform& other);

    glm::mat4 modelMatrix();
    glm::mat4 normalMatrix();

    void rotate(glm::vec3 euler);
    glm::vec3 forward();
    glm::vec3 right();
    glm::vec3 up();

    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0); // Euler angles
    glm::vec3 scale = glm::vec3(1);
};