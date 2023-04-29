#include "scene_manager.hpp"
#include "../gameengine/camera.hpp"
#include <algorithm>

Scene::Scene()
{
    Camera::currentCamera = nullptr;
}

void Scene::tick() {
    for(auto object : objects) {
        object->tick();
    }
}

void Scene::addObject(SteelObject* object) {
    objects.push_back(object);
}

void Scene::removeObject(SteelObject* object) {
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}
