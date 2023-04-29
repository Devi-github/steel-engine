#include "scene_manager.hpp"
#include "../gameengine/camera.hpp"

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
