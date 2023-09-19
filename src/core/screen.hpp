#pragma once

#include "../gameengine/camera.hpp"
#include "ray.hpp"

struct Screen {
    int width;
    int height;

    static Screen* instance;
};
