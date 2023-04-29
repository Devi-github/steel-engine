#include "camera.hpp"
#include "../core/application.hpp"
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
    glm::vec3 model = glm::vec4(0, 0, 1, 1) * glm::eulerAngleXYZ(transform.rotation.x, transform.rotation.y, transform.rotation.z);

    return glm::lookAt(transform.position, transform.position + model, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::projectionMatrix()
{
    return glm::perspective<float>(fov, BaseApplication::getInstance().Width / 
        (float)BaseApplication::getInstance().Height, nearClipPlane, farClipPlane);
}
