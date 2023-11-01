#include "functions.hpp"

SteelObject* duplicate(Scene &scene, SteelObject *object)
{
    if(object == nullptr) return nullptr;

    SteelObject* obj = object->duplicate();
    scene.addObject(obj);

    return obj;
}