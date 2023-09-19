#include "debug.hpp"

#include "primitives.hpp"
#include "../core/material.hpp"
#include "../core/shader.hpp"
#include "../core/components/transform.hpp"
#include "camera.hpp"

#include <GL/glew.h>

const float cubeVerts[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,

    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
};

const GLuint cubeIndices[] = {
    0, 1, 1, 2, 2, 3, 3, 0,

    4, 5, 5, 6, 6, 7, 7, 4,

    0, 4, 1, 5, 2, 6, 3, 7
    
    //4, 5, 5, 6,
    //6, 7, 7, 4
};

static Shader* debugShader = nullptr;
static Material* debugMaterial = nullptr;

static glm::vec3 gismosColor;

static GLuint cubevbo, cubevao, cubeebo;

void setup_debug() {
    debugShader = new Shader();
    debugShader->loadShaderFromFile("resources/unlit.vert", "resources/unlit.frag");
    debugMaterial = new Material();
    debugMaterial->loadShader(debugShader);

    glGenBuffers(1, &cubevbo);
    glGenBuffers(1, &cubeebo);
    glGenVertexArrays(1, &cubevao);

    glBindVertexArray(cubevao);
    
    glBindBuffer(GL_ARRAY_BUFFER, cubevbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec3 current_color() {
    return gismosColor;
}

void set_debug_color(glm::vec3 col) {
    gismosColor = col;
}

class Line {
    GLuint vbo, vao;
    std::vector<float> vertices;
    glm::vec3 startPoint, endPoint;
    glm::mat4 model;
public:
    Line(glm::vec3 p1, glm::vec3 p2) {
        startPoint = p1;
        endPoint = p2;
        model = glm::mat4(1.0f);
        
        vertices = {
            startPoint.x, startPoint.y, startPoint.z,
            endPoint.x, endPoint.y, endPoint.z
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Line() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void draw() {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        debugMaterial->use();

        debugMaterial->uniform4x4("model", model);
        debugMaterial->uniform4x4("view", Camera::currentCamera->viewMatrix());
        debugMaterial->uniform4x4("projection", Camera::currentCamera->projectionMatrix());

        debugMaterial->uniform3("objectColor", gismosColor);

        glDisable(GL_DEPTH_TEST);

        glDrawArrays(GL_LINES, 0, vertices.size());
        
        glEnable(GL_DEPTH_TEST);
    }
};

void draw_line(glm::vec3 p1, glm::vec3 p2) {
    Line line(p1, p2);

    line.draw();
}

void draw_wire_cube(glm::vec3 cpos, glm::vec3 scaling)
{
    if(Camera::currentCamera == nullptr)
        return;
        
    Transform t;
    t.position = cpos;
    t.scale = scaling;
    t.rotation = glm::vec3(0);

    glBindVertexArray(cubevao);
    glBindBuffer(GL_ARRAY_BUFFER, cubevbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeebo);

    debugMaterial->uniform4x4("model", t.modelMatrix());
    debugMaterial->uniform4x4("view", Camera::currentCamera->viewMatrix());
    debugMaterial->uniform4x4("projection", Camera::currentCamera->projectionMatrix());

    debugMaterial->uniform3("objectColor", gismosColor);

    glDrawElements(GL_LINES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
}