#include "transform.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform() {
}

glm::mat4 Transform::modelMatrix()
{
    return glm::mat4(1) * glm::translate(position) * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z) * glm::scale(scale);
}

void Transform::rotate(glm::vec3 euler)
{
    rotation += euler;
    if(rotation.x > glm::two_pi<float>()) rotation.x = 0;
    else if(rotation.x < 0) rotation.x = glm::two_pi<float>();
    if(rotation.y > glm::two_pi<float>()) rotation.y = 0;
    else if(rotation.y < 0) rotation.y = glm::two_pi<float>();
    if(rotation.z > glm::two_pi<float>()) rotation.z = 0;
    else if(rotation.z < 0) rotation.z = glm::two_pi<float>();
}

glm::vec3 Transform::forward()
{
    return glm::vec4(0, 0, 1, 1) * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
}

glm::vec3 Transform::right()
{
    return glm::vec4(-1, 0, 0, 1) * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
}

glm::vec3 Transform::up()
{
    return glm::vec4(0, 1, 0, 1) * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
}
