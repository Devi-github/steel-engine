#pragma once

#include <vector>

template <class T>
class ComponentContainer {
public:
    ComponentContainer();
    ~ComponentContainer();

    void addComponentInstance();
    
    std::vector<T*> container;
};

template <class T>
inline ComponentContainer<T>::ComponentContainer()
{
}

template <class T>
inline ComponentContainer<T>::~ComponentContainer()
{
    for(auto i = container.begin(); i < container.end(); i++) {
        delete i;
    }
}

template <class T>
inline void ComponentContainer<T>::addComponentInstance()
{
    T* component = new T();
    container.push_back(component);
}
