#pragma once
//#include "object.hpp"

class SteelObject;

class BaseComponent {
public:
    BaseComponent();

    virtual void onStart();
    virtual void onUpdate();

    SteelObject* steelObject;
};
