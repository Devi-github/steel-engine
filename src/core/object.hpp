#pragma once
#include <vector>
#include <map>
#include "component.hpp"
#include "components/transform.hpp"
#include <typeindex>

class SteelObject final {
public:
    SteelObject();

    Transform* transform;

    void tick();

    template <class T>
    T* addComponent() {
        static_assert(std::is_base_of<BaseComponent, T>::value, "Type must inherit base component class");
        auto newComponent = (BaseComponent*)new T();
        components.insert({typeid(T), newComponent});
        return (T*)newComponent;
    }

    template <class T>
    T* getComponent() {
        static_assert(std::is_base_of<BaseComponent, T>::value, "Type must inherit base component class");
        return (T*)components[typeid(T)];
    }
private:
    std::map<std::type_index, BaseComponent*> components;
};
