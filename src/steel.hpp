#pragma once
#include "core/application.hpp"
#include "core/steel_imgui.hpp"
#include "core/mesh.hpp"
#include "core/object.hpp"
#include "core/scene_manager.hpp"
#include "gameengine/camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <string>

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

    Camera editorCamera;

    SteelObject* chosenGameObject = nullptr;

    bool loaded = false;

private:
    void check_wireframe() {
        if(wireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    void init() override {
        BaseApplication::init();

        editorCamera.transform.position = glm::vec3(0, 0, 4);
        editorCamera.transform.rotation = glm::vec3(0, glm::pi<float>(), 0);

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

        Camera::currentCamera = &editorCamera;
    }
    void update(double time) override {
        BaseApplication::update(time);

        if(getMouseButton(1)) {
            setCursorMode(GLFW_CURSOR_DISABLED);
            controlCamera(time);
        } else {
            setCursorMode(GLFW_CURSOR_NORMAL);
        }
    }
    void controlCamera(double time) {
        editorCamera.transform.rotate(glm::vec3(-glm::radians(deltaMouseY) * 0.1, glm::radians(deltaMouseX) * 0.1, 0));

        if(getKey(GLFW_KEY_W)) {
            editorCamera.transform.position += editorCamera.transform.forward() * 0.1f;
        }
        if(getKey(GLFW_KEY_S)) {
            editorCamera.transform.position -= editorCamera.transform.forward() * 0.1f;
        }
        if(getKey(GLFW_KEY_A)) {
            editorCamera.transform.position -= editorCamera.transform.right() * 0.1f;
        }
        if(getKey(GLFW_KEY_D)) {
            editorCamera.transform.position += editorCamera.transform.right() * 0.1f;
        }
    }
    void render_main_bar() {
        ImGui::BeginMainMenuBar();

        if(ImGui::BeginMenu("File")) {
            if(ImGui::MenuItem("New Scene", "", false, false)) {
                std::cout << "New Scene is not yet implemented" << std::endl;
            }
            if(ImGui::MenuItem("Exit", "ALT+F4")) {
                stop();
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Edit")) {
            if(ImGui::MenuItem("Deselect", "CTRL+SHIFT+D", false, chosenGameObject != nullptr)) {
                chosenGameObject = nullptr;
            }
            if(ImGui::MenuItem("Duplicate", "CTRL+D", false, chosenGameObject != nullptr)) {
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

                obj->transform.position = chosenGameObject->transform.position;
                obj->transform.rotation = chosenGameObject->transform.rotation;
                obj->transform.scale = chosenGameObject->transform.scale;
                
                if(strlen(obj->name) < 128 - 8)
                    sprintf(obj->name, "%s (Copy)", obj->name);
                scene.addObject(obj);

                auto renderer = obj->addComponent<MeshRenderer>();
                renderer->setMesh(mesh);
                renderer->material = Material::Default();
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("SteelObject")) {
            if(ImGui::BeginMenu("Create Object")) {
                if(ImGui::MenuItem("New Test")) {
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
                    
                    strcpy(obj->name, "New Steel Object");

                    scene.addObject(obj);

                    auto renderer = obj->addComponent<MeshRenderer>();
                    renderer->setMesh(mesh);
                    renderer->material = Material::Default();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Window", false)) {
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    void render_object_list() {
        if(currentScene != nullptr) {
            ImGui::Begin("Object list");

            ImGui::BeginListBox("##");

            for(auto object : scene.objects) {
                char label[150];
                sprintf(label, "%s (0x%lx)", object->name, (unsigned long)object);
                std::string _label = label;
                if(ImGui::Selectable(_label.c_str(), false)) {
                    chosenGameObject = object;
                }
            }

            ImGui::EndListBox();

            ImGui::End();
        }
    }
    void render_ui() {
        imgui_newframe();

        render_main_bar();

        render_object_list();

        Transform& objtrans = chosenGameObject->transform;
        
        ImGui::Begin("Object information");
        if(chosenGameObject != nullptr) {
            ImGui::InputText("Name", chosenGameObject->name, 128);

            ImGui::DragFloat3("Position", (float*)&objtrans.position, 0.1f);
            ImGui::DragFloat3("Rotation", (float*)&objtrans.rotation, 0.05f);
            ImGui::DragFloat3("Scale", (float*)&objtrans.scale, 0.1f);
        }
        ImGui::End();

        ImGui::Begin("Camera");
        if(Camera::currentCamera != nullptr) {
            ImGui::Text("Position: X: %f Y: %f Z: %f", editorCamera.transform.position.x, 
                editorCamera.transform.position.y, editorCamera.transform.position.z);
            ImGui::Text("Look Direction: X: %f Y: %f Z: %f", editorCamera.transform.forward().x, 
                editorCamera.transform.forward().y, editorCamera.transform.forward().z);
        }
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
        if(k == GLFW_KEY_DELETE && a == GLFW_PRESS) {
            if(chosenGameObject != nullptr) {
                scene.removeObject(chosenGameObject);
                chosenGameObject = nullptr;
            }
        }
    }
    void onMouseButtonCallback(int k, int a, int m) override {

    }
    void onMouseCursorCallback(double xpos, double ypos) override {
        BaseApplication::onMouseCursorCallback(xpos, ypos);
    }
};
