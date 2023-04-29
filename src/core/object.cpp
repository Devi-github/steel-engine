#include "object.hpp"

SteelObject::SteelObject()
{
    components.insert({typeid(Transform), (BaseComponent*)(&transform)});
    transform.steelObject = (void*)this;
}

void SteelObject::tick() {
    std::map<std::type_index, BaseComponent*>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        it->second->onUpdate();
    }
}
