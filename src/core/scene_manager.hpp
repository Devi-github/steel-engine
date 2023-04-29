#pragma once
#include <glm/glm.hpp>
#include "object.hpp"

class Scene {
public:
    Scene();

    void tick();
    void addObject(SteelObject*);
    void removeObject(SteelObject*);

public:
    std::vector<SteelObject*> objects;
};
