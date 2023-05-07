#pragma once
//#include "object.hpp"

class SteelObject;

class BaseComponent {
public:
    BaseComponent();
    BaseComponent(const BaseComponent&);

    virtual void onStart();
    virtual void onUpdate();

    SteelObject* steelObject;
};
