#pragma once

#include "../core/components/transform.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    static Camera* currentCamera;

    glm::mat4 viewMatrix();
    glm::mat4 projectionMatrix();

    Transform transform;

    float nearClipPlane = 0.1, farClipPlane = 1000;

    // Field of view in radians
    float fov = glm::quarter_pi<float>();
};
