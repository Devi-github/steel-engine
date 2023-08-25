#pragma once
#include <vector>
#include <map>
#include <typeindex>
#include <string>
#include <iostream>

#include "components/transform.hpp"
#include "component_container.hpp"

class BaseComponent;

class SteelObject final {
public:
    SteelObject();
    SteelObject(std::string name);
    ~SteelObject();

    std::string name;

    Transform transform;

    void tick();

    SteelObject* duplicate();

    template <class T>
    T* addComponent() {
        static_assert(std::is_base_of<BaseComponent, T>::value, "Type must inherit base component class");
        std::cout << sizeof(T) << '\n';
        std::cout << sizeof(BaseComponent) << '\n';
        T* newComponent = new T();
        ((BaseComponent*)newComponent)->steelObject = this;
        components.insert({typeid(T), (BaseComponent*)newComponent});
        return newComponent;
    }

    template <class T>
    T* getComponent() {
        static_assert(std::is_base_of<BaseComponent, T>::value, "Type must inherit base component class");
        return (T*)components[typeid(T)];
    }
private:
    std::map<std::type_index, BaseComponent*> components;
};
