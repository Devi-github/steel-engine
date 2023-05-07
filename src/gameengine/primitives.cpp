#include "primitives.hpp"
#include <iostream>

const float cubeVertices[VERTEX_SIZE * 4 * 6] = {
    // Back face
    -0.5, -0.5, -0.5, 0, 0, -1, 0, 0,
    0.5, -0.5, -0.5, 0, 0, -1, 1, 0,
    0.5, 0.5, -0.5, 0, 0, -1, 1, 1,
    -0.5, 0.5, -0.5, 0, 0, -1, 0, 1,

    // Front face
    -0.5, -0.5, 0.5, 0, 0, 1, 0, 0,
    0.5, -0.5, 0.5, 0, 0, 1, 1, 0,
    0.5, 0.5, 0.5, 0, 0, 1, 1, 1,
    -0.5, 0.5, 0.5, 0, 0, 1, 0, 1,

    // Left face
    -0.5, -0.5, -0.5, -1, 0, 0, 0, 0,
    -0.5, -0.5, 0.5, -1, 0, 0, 1, 0,
    -0.5, 0.5, 0.5, -1, 0, 0, 1, 1,
    -0.5, 0.5, -0.5, -1, 0, 0, 0, 1,

    // Right face
    0.5, -0.5, -0.5, 1, 0, 0, 0, 0,
    0.5, -0.5, 0.5, 1, 0, 0, 1, 0,
    0.5, 0.5, 0.5, 1, 0, 0, 1, 1,
    0.5, 0.5, -0.5, 1, 0, 0, 0, 1,

    // Top face
    -0.5, 0.5, -0.5, 0, 1, 0, 0, 0,
    0.5, 0.5, -0.5, 0, 1, 0, 1, 0,
    0.5, 0.5, 0.5, 0, 1, 0, 1, 1,
    -0.5, 0.5, 0.5, 0, 1, 0, 0, 1,

    // Bottom face
    -0.5, -0.5, -0.5, 0, -1, 0, 0, 0,
    0.5, -0.5, -0.5, 0, -1, 0, 1, 0,
    0.5, -0.5, 0.5, 0, -1, 0, 1, 1,
    -0.5, -0.5, 0.5, 0, -1, 0, 0, 1,
};
const float planeVertices[VERTEX_SIZE * 4] = {
    -0.5, 0, -0.5, 0, 1, 0, 0, 0,
    0.5, 0, -0.5, 0, 1, 0, 1, 0,
    0.5, 0, 0.5, 0, 1, 0, 1, 1,
    -0.5, 0, 0.5, 0, 1, 0, 0, 1,
};
const GLuint cubeIndices[6 * 6] = {
    // Back face
    0, 2, 1,
    0, 3, 2,

    // Front face
    4, 5, 6,
    4, 6, 7,

    // Left face
    8, 9, 10,
    8, 10, 11,

    // Right face
    12, 14, 13,
    12, 15, 14,

    // Top face
    16, 18, 17,
    16, 19, 18,

    // Bottom face
    20, 21, 22,
    20, 22, 23,
};
const GLuint planeIndices[6] = {
    0, 2, 1,
    0, 3, 2
};

Mesh* constructMesh(Primitives primitive)
{
    float* vertexBuffer;
    GLuint* indicesBuffer;
    int vertexCount;

    switch(primitive) {
        case Primitives::CUBE:
        vertexBuffer = (float*)malloc(sizeof(cubeVertices));
        indicesBuffer = (GLuint*)malloc(sizeof(cubeIndices));
        memcpy(vertexBuffer, cubeVertices, sizeof(cubeVertices));
        memcpy(indicesBuffer, cubeIndices, sizeof(cubeIndices));
        vertexCount = sizeof(cubeIndices) / sizeof(GLuint);
        break;
        case Primitives::SPHERE:
        std::cerr << "Sphere mesh is not yet implemented\n";
        return nullptr; // TODO: Placeholder
        case Primitives::PLANE:
        vertexBuffer = (float*)malloc(sizeof(planeVertices));
        indicesBuffer = (GLuint*)malloc(sizeof(planeIndices));
        memcpy(vertexBuffer, planeVertices, sizeof(planeVertices));
        memcpy(indicesBuffer, planeIndices, sizeof(planeIndices));
        vertexCount = sizeof(planeIndices) / sizeof(GLuint);
        break;
        default:
        return nullptr;
    }

    return new Mesh(vertexBuffer, indicesBuffer, vertexCount);
}