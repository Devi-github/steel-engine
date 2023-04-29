#include "transform.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform() {
}

glm::mat4 Transform::modelMatrix()
{
    return glm::mat4(1) * glm::scale(scale) * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z) * glm::translate(position);
}

void Transform::rotate(glm::vec3 euler)
{
    rotation += euler;
    if(rotation.x > 360) rotation.x = 0;
    else if(rotation.x < 0) rotation.x = 360;
    if(rotation.y > 360) rotation.y = 0;
    else if(rotation.y < 0) rotation.y = 360;
    if(rotation.z > 360) rotation.z = 0;
    else if(rotation.z < 0) rotation.z = 360;
}
