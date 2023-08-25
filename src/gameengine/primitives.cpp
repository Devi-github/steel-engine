#include "primitives.hpp"

#include <iostream>
#include <memory>
#include <cmath>

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

static Mesh* boxMesh = nullptr;
static Mesh* sphereMesh = nullptr;
static Mesh* planeMesh = nullptr;

/*
 * Credit goes to http://www.songho.ca/opengl/gl_sphere.html
 * // FIXME: A lot of triangles generated on the inside. May impact performance
 */
void generateSphere(float radius, int sector_count, int stack_count, float** outVertices, GLuint** outIndices) {
    std::vector<float> vertexData;

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * M_PI / sector_count;
    float stackStep = M_PI / stack_count;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stack_count; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sector_count; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertexData.push_back(nx);
            vertexData.push_back(ny);
            vertexData.push_back(nz);

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sector_count;
            t = (float)i / stack_count;
            vertexData.push_back(s);
            vertexData.push_back(t);
        }
    }
    std::vector<int> indices;
    std::vector<int> lineIndices;
    int k1, k2;
    for(int i = 0; i < stack_count; ++i)
    {
        k1 = i * (sector_count + 1);     // beginning of current stack
        k2 = k1 + sector_count + 1;      // beginning of next stack

        for(int j = 0; j < sector_count; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stack_count-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

            // store indices for lines
            // vertical lines for all stacks, k1 => k2
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            if(i != 0)  // horizontal lines except 1st stack, k1 => k+1
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }
        }
    }

    *outVertices = (float*)malloc(vertexData.size() * sizeof(float));
    *outIndices = (GLuint*)malloc(indices.size() * sizeof(GLuint));

    memcpy(*outVertices, vertexData.data(), vertexData.size() * sizeof(float));
    memcpy(*outIndices, indices.data(), indices.size() * sizeof(GLuint));
}

Mesh* constructMesh(Primitives primitive)
{
    float* vertexBuffer;
    GLuint* indicesBuffer;
    int vertexCount;

    Mesh* resultMesh;

    switch(primitive) {
        case Primitives::CUBE:
        if(boxMesh != nullptr) return boxMesh;
        vertexBuffer = (float*)malloc(sizeof(cubeVertices));
        indicesBuffer = (GLuint*)malloc(sizeof(cubeIndices));
        memcpy(vertexBuffer, cubeVertices, sizeof(cubeVertices));
        memcpy(indicesBuffer, cubeIndices, sizeof(cubeIndices));
        vertexCount = sizeof(cubeIndices) / sizeof(GLuint);
        resultMesh = new Mesh(vertexBuffer, indicesBuffer, vertexCount);
        boxMesh = resultMesh;
        break;
        case Primitives::SPHERE:
        if(sphereMesh != nullptr) return sphereMesh;
        float* vx;
        GLuint* ind;
        generateSphere(1, 32, 32, &vx, &ind);
        vertexBuffer = vx;
        indicesBuffer = ind;
        resultMesh = new Mesh(vertexBuffer, indicesBuffer, vertexCount);
        sphereMesh = resultMesh;
        break;
        case Primitives::PLANE:
        if(planeMesh != nullptr) return planeMesh;
        vertexBuffer = (float*)malloc(sizeof(planeVertices));
        indicesBuffer = (GLuint*)malloc(sizeof(planeIndices));
        memcpy(vertexBuffer, planeVertices, sizeof(planeVertices));
        memcpy(indicesBuffer, planeIndices, sizeof(planeIndices));
        vertexCount = sizeof(planeIndices) / sizeof(GLuint);
        resultMesh = new Mesh(vertexBuffer, indicesBuffer, vertexCount);
        planeMesh = resultMesh;
        break;
        default:
        return nullptr;
    }

    free(vertexBuffer);
    free(indicesBuffer);

    return resultMesh;
}