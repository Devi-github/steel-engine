#include "mesh.hpp"
#include "../gameengine/camera.hpp"
#include "object.hpp"
#include "scene_manager.hpp"

Mesh::Mesh() {

}
Mesh::Mesh(float *buffer, GLuint* indbuff, int vxCount, int idCount)
{
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    vertexSize = VERTEX_SIZE;

    vertexBuffer = (float*)malloc(vxCount * VERTEX_SIZE * sizeof(float));
    indices = (GLuint*)malloc(idCount * sizeof(GLuint));
    vertexCount = vxCount;
    indicesCount = idCount;

    memcpy(vertexBuffer, buffer, vxCount * VERTEX_SIZE * sizeof(float));
    memcpy(indices, indbuff, idCount * sizeof(GLuint));

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * vertexSize, vertexBuffer, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * idCount, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, vertexSize * sizeof(float), (void*)(0)); // vertex position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, vertexSize * sizeof(float), (void*)(3 * sizeof(float))); // vertex normal
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, false, vertexSize * sizeof(float), (void*)(6 * sizeof(float))); // vertex uv
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
Mesh::Mesh(const Mesh &mesh)
{
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    vertexSize = VERTEX_SIZE;

    vertexBuffer = (float*)malloc(mesh.vertexCount * VERTEX_SIZE * sizeof(float));
    indices = (GLuint*)malloc(mesh.indicesCount * sizeof(GLuint));
    vertexCount = mesh.vertexCount;
    indicesCount = mesh.indicesCount;
    memcpy(vertexBuffer, mesh.vertexBuffer, mesh.vertexCount * VERTEX_SIZE * sizeof(float));
    memcpy(indices, mesh.indices, mesh.indicesCount * sizeof(GLuint));

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * vertexSize, vertexBuffer, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicesCount, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, vertexSize * sizeof(float), (void*)(0)); // vertex position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, vertexSize * sizeof(float), (void*)(3 * sizeof(float))); // vertex normal
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, false, vertexSize * sizeof(float), (void*)(6 * sizeof(float))); // vertex uv
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
Mesh::~Mesh()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);

    free(vertexBuffer);
    free(indices);
}

glm::vec3 Mesh::findMaxBound()
{
    glm::vec3 minBound = glm::vec3(INFINITY);
    for(int i = 0; i < vertexCount * vertexSize; i += vertexSize) {
        float x = vertexBuffer[i + 0];
        float y = vertexBuffer[i + 1];
        float z = vertexBuffer[i + 2];

        if(x < minBound.x) minBound.x = x;
        if(y < minBound.y) minBound.y = y;
        if(z < minBound.z) minBound.z = z;
    }
    return minBound;
}

glm::vec3 Mesh::findMinBound()
{
    glm::vec3 maxBound = glm::vec3(-INFINITY);
    for(int i = 0; i < vertexCount * vertexSize; i += vertexSize) {
        float x = vertexBuffer[i + 0];
        float y = vertexBuffer[i + 1];
        float z = vertexBuffer[i + 2];

        if(x > maxBound.x) maxBound.x = x;
        if(y > maxBound.y) maxBound.y = y;
        if(z > maxBound.z) maxBound.z = z;
    }
    return maxBound;
}

glm::vec3 Mesh::findMinBoundWithModel(glm::mat4 model)
{
    glm::vec3 minBound = glm::vec3(INFINITY);
    for(int i = 0; i < vertexCount * vertexSize; i += vertexSize) {
        float x = vertexBuffer[i + 0];
        float y = vertexBuffer[i + 1];
        float z = vertexBuffer[i + 2];

        glm::vec4 tmp(x, y, z, 1);
        tmp = model * tmp;

        if(tmp.x < minBound.x) minBound.x = tmp.x;
        if(tmp.y < minBound.y) minBound.y = tmp.y;
        if(tmp.z < minBound.z) minBound.z = tmp.z;
    }
    return minBound;
}

glm::vec3 Mesh::findMaxBoundWithModel(glm::mat4 model)
{
    glm::vec3 maxBound = glm::vec3(-INFINITY);
    for(int i = 0; i < vertexCount * vertexSize; i += vertexSize) {
        float x = vertexBuffer[i + 0];
        float y = vertexBuffer[i + 1];
        float z = vertexBuffer[i + 2];

        glm::vec4 tmp(x, y, z, 1);
        tmp = model * tmp;

        if(tmp.x > maxBound.x) maxBound.x = tmp.x;
        if(tmp.y > maxBound.y) maxBound.y = tmp.y;
        if(tmp.z > maxBound.z) maxBound.z = tmp.z;
    }
    return maxBound;
}

MeshRenderer::MeshRenderer() {
    
}

MeshRenderer::MeshRenderer(const MeshRenderer &other) : BaseComponent(other)
{
    setMesh(other.mesh);
}
MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::setMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

void MeshRenderer::draw(GLenum type)
{
    if(Scene::currentScene == nullptr || Camera::currentCamera == nullptr) return;

    if(sharedMaterial != nullptr)
        sharedMaterial->use();
    else if(material != nullptr)
        material->use();
    else
        return;

    glBindVertexArray(mesh->vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

    auto model = steelObject->transform.modelMatrix();
    auto normMat = steelObject->transform.normalMatrix();

    if(sharedMaterial != nullptr) {
        sharedMaterial->uniform4x4("model", model);
        sharedMaterial->uniform4x4("normalMatrix", normMat);
        sharedMaterial->uniform4x4("view", Camera::currentCamera->viewMatrix());
        sharedMaterial->uniform4x4("projection", Camera::currentCamera->projectionMatrix());
        sharedMaterial->uniform3("lightDirection", Scene::currentScene->light.direction);
        sharedMaterial->uniform3("lightColor", Scene::currentScene->light.color);
        sharedMaterial->uniform1("lightIntensity", Scene::currentScene->light.intensity);
        sharedMaterial->uniform3("ambient", Scene::currentScene->backgroundColor);
        sharedMaterial->uniform1("ambientStrength", 0.1);
    } else {
        material->uniform4x4("model", model);
        material->uniform4x4("normalMatrix", normMat);
        material->uniform4x4("view", Camera::currentCamera->viewMatrix());
        material->uniform4x4("projection", Camera::currentCamera->projectionMatrix());
        material->uniform3("lightDirection", Scene::currentScene->light.direction);
        material->uniform3("lightColor", Scene::currentScene->light.color);
        material->uniform1("lightIntensity", Scene::currentScene->light.intensity);
        material->uniform3("ambient", Scene::currentScene->backgroundColor);
        material->uniform1("ambientStrength", 1);
    }

    glDrawElements(type, mesh->indicesCount, GL_UNSIGNED_INT, 0);
}

void MeshRenderer::onUpdate() {
    draw(drawType);
}
