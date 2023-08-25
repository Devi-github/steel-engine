#include "object.hpp"
#include "component.hpp"
#include "mesh.hpp"

#include <cstring>
#include <iostream>
#include <fmt/core.h>

SteelObject::SteelObject() : name("SteelGameObject")
{
    components.insert({typeid(Transform), (BaseComponent*)(&transform)});
}

SteelObject::SteelObject(std::string name) : name(name)
{
}

SteelObject::~SteelObject() {

}

void SteelObject::tick() {
    std::map<std::type_index, BaseComponent*>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        it->second->onUpdate();
    }
}

SteelObject *SteelObject::duplicate()
{
    SteelObject* obj = new SteelObject();

    obj->transform.copyTransform(transform);

    name += " (Copy)";

    auto thisRenderer = getComponent<MeshRenderer>();
    if(thisRenderer == nullptr) return obj;
    
    //Mesh *mesh = new Mesh(*thisRenderer->mesh);

    auto newRenderer = obj->addComponent<MeshRenderer>();
    newRenderer->setMesh(thisRenderer->mesh);
    newRenderer->sharedMaterial = thisRenderer->sharedMaterial;
    
    return obj;
}
