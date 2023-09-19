#include "camera.hpp"
#include "../core/application.hpp"
#include "../core/screen.hpp"

#include <glm/gtx/euler_angles.hpp>

Camera::Camera()
{
    transform.position = glm::vec3(0, 0, 0);
    transform.rotation = glm::vec3(0, 0, 0);
}

Camera::~Camera()
{
    
}

glm::mat4 Camera::viewMatrix()
{
    return glm::lookAt(transform.position, transform.position + transform.forward(), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::projectionMatrix()
{
    return glm::perspective<float>(fov, BaseApplication::getInstance().Width / 
        (float)BaseApplication::getInstance().Height, nearClipPlane, farClipPlane);
}

glm::vec2 Camera::worldToScreenSpace(glm::vec3 world) {
    glm::mat4 mtx = glm::translate(world) * viewMatrix() * projectionMatrix();
    glm::vec4 result = glm::vec4(0, 0, 0, 1) * mtx;
    return glm::vec2(result.x, result.y);
}

Ray Camera::rayFromCameraScreenSpace(glm::vec2 point) {
    Ray result;
    float x = (2.0 * point.x) / (float)Screen::instance->width - 1.0;
    float y = 1.0 - (2.0 * point.y) / (float)Screen::instance->height;
    float z = 1.0;

    glm::vec3 ray_nds = glm::vec3(x, y, z);
    result.origin = transform.position;
    result.direction = glm::normalize(ray_nds);

    return result;
}
