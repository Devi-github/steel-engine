#include "object.hpp"

SteelObject::SteelObject()
{
    auto trans = (BaseComponent*)new Transform();
    components.insert({typeid(Transform), trans});
    transform = (Transform*)trans;
}

void SteelObject::tick() {
    std::map<std::type_index, BaseComponent*>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        it->second->onUpdate();
    }
}
