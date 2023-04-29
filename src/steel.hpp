#pragma once
#include "core/application.hpp"
#include "core/steel_imgui.hpp"
#include "core/mesh.hpp"
#include "core/object.hpp"
#include "core/scene_manager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Scene* currentScene = nullptr;

class SteelMain final : public BaseApplication {
public:
    SteelMain(int w, int h) :
    BaseApplication(w, h, "Steel Engine") {
        currentScene = nullptr;
    }

private:
    bool wireframeMode = false;

    Scene scene;
    bool loaded = false;

private:
    void check_wireframe() {
        if(wireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    void init() override {
        BaseApplication::init();

        glClearColor(0.3, 0.7, 1, 1);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        float vbuf[] = {
            -0.5, -0.5, 0, 0, 0, -1, 0, 0,
            0.5, -0.5, 0, 0, 0, -1, 1, 0,
            0, 0.5, 0, 0, 0, -1, 0.5, 1,
            0.8, 0.5, 0, 0, 0, -1, 0.9, 1,
        };
        GLuint indices[] = {
            0, 1, 2,
            1, 3, 2
        };

        Mesh* mesh = new Mesh(vbuf, indices, sizeof(indices) / sizeof(GLuint));

        SteelObject* obj = new SteelObject();

        scene.addObject(obj);

        auto renderer = obj->addComponent<MeshRenderer>();
        renderer->setMesh(mesh);
        renderer->material = Material::Default();

        currentScene = &scene;
    }
    void update(double time) override {
        BaseApplication::update(time);

        if(getMouseButton(1)) {
            
        }
    }
    void render_ui() {
        imgui_newframe();
        ImGui::BeginMainMenuBar();

        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("New Scene")) {
                std::cout << "New Scene is not yet implemented" << std::endl;
            }
            if(ImGui::MenuItem("Exit")) {
                stop();
            }
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();

        ImGui::Begin("Create object");

        ImGui::End();
        imgui_render();
    }
    void render(double time) override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(currentScene == nullptr && !loaded) {
            std::cerr << "No scene loaded" << std::endl;
            stop(1);
            return;
        }

        currentScene->tick();

        render_ui();

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
