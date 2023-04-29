#include "object.hpp"

SteelObject::SteelObject()
{
    auto trans = (BaseComponent*)new Transform();
    components.insert({typeid(Transform), trans});
    transform = (Transform*)trans;
}

/*template <class T>
void SteelObject::addComponent()
{
    static_assert(std::is_base_of<BaseComponent, T>::value, "Type must inherit base component class");
    auto newComponent = (BaseComponent*)new T();
    newComponent->gameObject = this;
    components.push_back(newComponent);
}

template <class T>
T* SteelObject::getComponent()
{
    static_assert(std::is_base_of<BaseComponent, T>::value, "Type must inherit base component class");
    for(auto component : components) {
        if(typeid(component) == typeid(T)) return component;
    }
    return nullptr;
}*/
