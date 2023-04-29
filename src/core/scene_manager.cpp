#include "scene_manager.hpp"

Scene::Scene()
{

}

void Scene::tick() {
    for(auto object : objects) {
        object->tick();
    }
}

void Scene::addObject(SteelObject* object) {
    objects.push_back(object);
}
