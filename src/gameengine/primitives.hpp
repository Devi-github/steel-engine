#pragma once
#include <GL/glew.h>
#include "../core/mesh.hpp"

enum Primitives {
    CUBE, SPHERE,
    PLANE
};

Mesh* constructMesh(Primitives primitive);
