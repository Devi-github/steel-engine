#pragma once
#include <GL/glew.h>
#include "../core/mesh.hpp"

enum Primitives {
    CUBE, SPHERE,
    PLANE
};

void generateSphere(float radius, int sector_count, int stack_count, float** outVertices, GLuint** outIndices);
Mesh* constructMesh(Primitives primitive);
