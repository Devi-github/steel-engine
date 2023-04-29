#include "mesh.hpp"
#include "../gameengine/camera.hpp"
#include "object.hpp"

Mesh::Mesh() {

}
Mesh::Mesh(float *buffer, GLuint* indbuff, int vxCount)
{
    vertexSize = 8;

    vertexBuffer = buffer;
    vertexCount = vxCount;
    indices = indbuff;
}
Mesh::~Mesh() {
    delete vertexBuffer;
    delete indices;
}

MeshRenderer::MeshRenderer() {
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
}

MeshRenderer::~MeshRenderer()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void MeshRenderer::setMesh(Mesh* mesh)
{
    this->mesh = mesh;

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->vertexCount * mesh->vertexSize, mesh->vertexBuffer, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->vertexCount, mesh->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, mesh->vertexSize * sizeof(float), (void*)(0)); // vertex position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, mesh->vertexSize * sizeof(float), (void*)(3 * sizeof(float))); // vertex normal
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, false, mesh->vertexSize * sizeof(float), (void*)(6 * sizeof(float))); // vertex uv
    glEnableVertexAttribArray(2);
}

void MeshRenderer::draw(GLenum type)
{
    material->use();

    auto model = ((SteelObject*)steelObject)->transform.modelMatrix();

    material->uniform4x4("model", model);
    material->uniform4x4("view", Camera::currentCamera->viewMatrix());
    material->uniform4x4("projection", Camera::currentCamera->projectionMatrix());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindVertexArray(vao);
    glDrawElements(type, mesh->vertexCount, GL_UNSIGNED_INT, 0);
}

void MeshRenderer::onUpdate() {
    draw(drawType);
}
