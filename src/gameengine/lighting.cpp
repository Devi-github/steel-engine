#include "lighting.hpp"

DirectionalLight::DirectionalLight()
{
    direction = glm::normalize(-glm::vec3(2, 1, 1));
    intensity = 1;
    color = glm::vec3(1);
}