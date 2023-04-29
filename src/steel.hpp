#pragma once
#include "core/application.hpp"
#include "core/steel_imgui.hpp"
#include "core/mesh.hpp"
#include "core/object.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class SteelMain final : public BaseApplication {
public:
    SteelMain(int w, int h) :
    BaseApplication(w, h, "Steel Engine") {

    }
private:
    bool wireframeMode = false;

    SteelObject* obj;

private:
    void check_wireframe() {
        if(wireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    void init() override {
        BaseApplication::init();

        glClearColor(0.3, 0.7, 1, 1);

        glEnable(GL_DEPTH_TEST);

        float vbuf[24] = {
            -0.5, -0.5, 0, 0, 0, -1, 0, 0,
            0.5, -0.5, 0, 0, 0, -1, 1, 0,
            0, 0.5, 0, 0, 0, -1, 0.5, 1,
        };
        GLuint indices[3] = {
            0, 1, 2
        };

        Mesh* mesh = new Mesh(vbuf, indices, sizeof(indices) / sizeof(GLuint));

        obj = new SteelObject();

        auto renderer = obj->addComponent<MeshRenderer>();
        renderer->setMesh(mesh);
        renderer->material = Material::Default();
    }
    void update(double time) override {
        BaseApplication::update(time);
    }
    void render(double time) override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        imgui_newframe();

        obj->getComponent<MeshRenderer>()->draw(GL_TRIANGLES);

        ImGui::Begin("Create object");

        ImGui::End();

        imgui_render();

        check_wireframe();
        swapBuffers();
        BaseApplication::render(time);
    }
    void onEnd() override {
        BaseApplication::onEnd();
    }
    void onKeyCallback(int k, int sc, int a, int m) override {

    }
    void onMouseButtonCallback(int k, int a, int m) override {

    }
    void onMouseCursorCallback(double xpos, double ypos) override {

    }
};
