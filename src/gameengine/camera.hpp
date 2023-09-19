#pragma once

#include "../core/components/transform.hpp"
#include "../core/ray.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    static Camera* currentCamera;

    glm::mat4 viewMatrix();
    glm::mat4 projectionMatrix();
    glm::vec2 worldToScreenSpace(glm::vec3 world);
    Ray rayFromCameraScreenSpace(glm::vec2 point);

    Transform transform;

    float fieldOfView = 1;

    float nearClipPlane = 0.1, farClipPlane = 1000;

    // Field of view in radians
    float fov = glm::pi<float>() / 3;
};
