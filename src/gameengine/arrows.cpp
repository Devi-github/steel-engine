#include "arrows.hpp"

#include "../core/shader.hpp"
#include "../core/material.hpp"
#include "camera.hpp"

#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

const float arrowBody[] = { // Looking right
    // Arrow body
    0, 0, 0,
    1, 0, 0,

    // Arrow head
    0.8f, 0.05f, 0,
    1, 0, 0,
    0.8f, -0.05f, 0
};

class MoveArrow : public IArrow {
public:
    MoveArrow();
    ~MoveArrow();
    void draw(glm::vec3 position) override;

    bool XBB(glm::vec3 position, glm::vec3 direction);
    bool YBB(glm::vec3 position, glm::vec3 direction);
    bool ZBB(glm::vec3 position, glm::vec3 direction);
private:
    GLuint vbo, vao;
};

static Shader* arrowShader;
static Material* arrowMaterial;
static MoveArrow* moveArrow;

const char* arrowVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 vertexPos;\n"
"uniform mat4 model, view, projection;\n"
"void main() {\n"
"gl_Position = vec4(vertexPos, 1) * model * view * projection;\n"
"}\n";

const char* arrowFragmentShader = "#version 330 core\n"
"out vec4 fragColor;\n"
"uniform vec3 color;\n"
"void main() {\n"
"fragColor = vec4(color, 1);\n"
"}\n";

void setup_arrows()
{
    arrowShader = new Shader();
    arrowShader->loadShaders(arrowVertexShader, arrowFragmentShader);
    arrowMaterial = new Material();
    arrowMaterial->loadShader(arrowShader);
    moveArrow = new MoveArrow();
}

void draw_move_arrows(glm::vec3 position)
{
    moveArrow->draw(position);
}

void draw_scale_arrows(glm::vec3 position)
{

}

void draw_rotate_sphere(glm::vec3 position) {

}

MoveArrow::MoveArrow()
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);

    glBufferData(GL_ARRAY_BUFFER, sizeof(arrowBody), arrowBody, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

MoveArrow::~MoveArrow()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void MoveArrow::draw(glm::vec3 position)
{
    if(Camera::currentCamera == nullptr) return;

    glm::mat4 model = glm::translate(position);

    glClear(GL_DEPTH_BUFFER_BIT);
    glLineWidth(4);

    arrowMaterial->use();

    glBindVertexArray(vao);

    arrowMaterial->uniform4x4("view", Camera::currentCamera->viewMatrix());
    arrowMaterial->uniform4x4("projection", Camera::currentCamera->projectionMatrix());

    arrowMaterial->uniform3("color", glm::vec3(1, 0, 0));
    arrowMaterial->uniform4x4("model", model);

    glDrawArrays(GL_LINES, 0, 2);

    glCullFace(GL_FRONT);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glCullFace(GL_BACK);
    glDrawArrays(GL_TRIANGLES, 2, 3);

    arrowMaterial->uniform3("color", glm::vec3(0, 1, 0));
    arrowMaterial->uniform4x4("model", glm::translate(position) * glm::eulerAngleXYZ(0.0f, 0.0f, glm::half_pi<float>()));

    glDrawArrays(GL_LINES, 0, 2);
    glCullFace(GL_FRONT);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glCullFace(GL_BACK);
    glDrawArrays(GL_TRIANGLES, 2, 3);

    arrowMaterial->uniform3("color", glm::vec3(0, 0, 1));
    arrowMaterial->uniform4x4("model", glm::translate(position) * glm::eulerAngleXYZ(0.0f, glm::half_pi<float>(), 0.0f));

    glDrawArrays(GL_LINES, 0, 2);
    glCullFace(GL_FRONT);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glCullFace(GL_BACK);
    glDrawArrays(GL_TRIANGLES, 2, 3);
}

bool testBB(glm::vec3 pos, glm::vec3 dir, glm::vec3 aabb_min, glm::vec3 aabb_max) {
    float tMin = 0;
    float tmax = 100000;

    
}

bool MoveArrow::XBB(glm::vec3 position, glm::vec3 direction)
{
    
    return false;
}

bool MoveArrow::YBB(glm::vec3 position, glm::vec3 direction)
{
    return false;
}

bool MoveArrow::ZBB(glm::vec3 position, glm::vec3 direction)
{
    return false;
}