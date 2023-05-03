#include "object.hpp"
#include "component.hpp"
#include <cstring>

SteelObject::SteelObject()
{
    strcpy(name, "SteelGameObject");
    
    components.insert({typeid(Transform), (BaseComponent*)(&transform)});
    transform.steelObject = this;
}

void SteelObject::tick() {
    std::map<std::type_index, BaseComponent*>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        it->second->onUpdate();
    }
}
