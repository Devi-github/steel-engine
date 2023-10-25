#pragma once
#include "core/application.hpp"
#include "core/steel_imgui.hpp"
#include "core/mesh.hpp"
#include "core/object.hpp"
#include "core/scene_manager.hpp"
#include "core/shader.hpp"
#include "core/screen.hpp"

#include "gameengine/ui.hpp"
#include "gameengine/debug.hpp"
#include "gameengine/camera.hpp"
#include "gameengine/primitives.hpp"
#include "gameengine/arrows.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <string>
#include <sstream>

class SteelMain final : public BaseApplication {
public:
    SteelMain(int w, int h) :
    BaseApplication(w, h, "Steel Engine") {
        sprintf(title, "Steel Engine | %dx%d | OGL %s", Width, Height, glGetString(GL_VERSION));
        Scene::currentScene = nullptr;
    }

private:
    bool wireframeMode = false;

    Scene scene;

    Camera editorCamera;
    float cameraSpeed = 0.1f;

    SteelObject* chosenGameObject = nullptr;

    Material* mainMaterial;

    bool loaded = false;

    int allVertices = 0;
    int allFaces = 0;

private:
    void check_wireframe() {
        if(wireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);
        }
    }
    void init() override {
        BaseApplication::init();

        editorCamera.transform.position = glm::vec3(0, 1, 4);
        editorCamera.transform.rotation = glm::vec3(0, glm::pi<float>(), 0);

        scene.backgroundColor = glm::vec3(0.3, 0.7, 1);

        glClearColor(scene.backgroundColor.x, scene.backgroundColor.y, scene.backgroundColor.z, 1);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        mainMaterial = Material::Default();
        mainMaterial->uniform3("objectColor", glm::vec3(1, 0.2, 0.2));

        Scene::currentScene = &scene;

        Camera::currentCamera = &editorCamera;

        setup_debug();
        set_debug_color(glm::vec3(1));
        setup_arrows();
        setVsync(1); // set vsync to 1
    }
    void update(double time) override {
        BaseApplication::update(time);

        allVertices = 0;
        allFaces = 0;

        for(auto object : Scene::currentScene->objects) {
            auto renderer = object->getComponent<MeshRenderer>();
            if(renderer != nullptr) {
                allVertices += renderer->mesh->vertexCount;
                allFaces += renderer->mesh->indicesCount / 3; // Assuming triangles
            }
        }

        if(getMouseButton(1)) {
            setCursorMode(GLFW_CURSOR_DISABLED);
            controlCamera(time);
        } else {
            setCursorMode(GLFW_CURSOR_NORMAL);
        }
    }
    void controlCamera(double time) {
        constexpr float SPEED_MULTIPLIER = 25.0f;
        editorCamera.transform.rotate(glm::vec3(-glm::radians(deltaMouseY) * 0.1, glm::radians(deltaMouseX) * 0.1, 0));

        if(getKey(GLFW_KEY_W)) {
            editorCamera.transform.position += editorCamera.transform.forward() * cameraSpeed * SPEED_MULTIPLIER * (float)time;
        }
        if(getKey(GLFW_KEY_S)) {
            editorCamera.transform.position -= editorCamera.transform.forward() * cameraSpeed * SPEED_MULTIPLIER * (float)time;
        }
        if(getKey(GLFW_KEY_A)) {
            editorCamera.transform.position -= editorCamera.transform.right() * cameraSpeed * SPEED_MULTIPLIER * (float)time;
        }
        if(getKey(GLFW_KEY_D)) {
            editorCamera.transform.position += editorCamera.transform.right() * cameraSpeed * SPEED_MULTIPLIER * (float)time;
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
                duplicate();
            }
            ImGui::EndMenu();
        }
// FIXME: I don't know why, but creating new objects overwrites a previously created object's mesh
        if(ImGui::BeginMenu("SteelObject")) {
            if(ImGui::BeginMenu("Create Object")) {
                if(ImGui::MenuItem("New Cube")) {
                    SteelObject* obj = new SteelObject();
                    
                    obj->name = "New Cube";

                    scene.addObject(obj);

                    auto renderer = obj->addComponent<MeshRenderer>();
                    renderer->setMesh(constructMesh(Primitives::CUBE));

                    renderer->material = Material::Default();

                    float rnd = rand() / (float)RAND_MAX;

                    renderer->material->uniform3("objectColor", 
                        glm::vec3(
                            rand() / (float)RAND_MAX, 
                            rand() / (float)RAND_MAX, 
                            rand() / (float)RAND_MAX
                        )
                    );

                    chosenGameObject = obj;
                }
                if(ImGui::MenuItem("New Plane")) {
                    SteelObject* obj = new SteelObject();
                    
                    obj->name = "New Plane";

                    scene.addObject(obj);

                    auto renderer = obj->addComponent<MeshRenderer>();
                    renderer->setMesh(constructMesh(Primitives::PLANE));

                    renderer->material = Material::Default();

                    float rnd = rand() / (float)RAND_MAX;

                    renderer->material->uniform3("objectColor", 
                        glm::vec3(
                            rand() / (float)RAND_MAX, 
                            rand() / (float)RAND_MAX, 
                            rand() / (float)RAND_MAX
                        )
                    );

                    chosenGameObject = obj;
                }
                if(ImGui::MenuItem("New Sphere")) {
                    SteelObject* obj = new SteelObject();

                    obj->name = "New Sphere";

                    scene.addObject(obj);

                    auto renderer = obj->addComponent<MeshRenderer>();
                    renderer->setMesh(constructMesh(Primitives::SPHERE));

                    renderer->material = Material::Default();

                    float rnd = rand() / (float)RAND_MAX;

                    renderer->material->uniform3("objectColor", 
                        glm::vec3(
                            rand() / (float)RAND_MAX, 
                            rand() / (float)RAND_MAX, 
                            rand() / (float)RAND_MAX
                        )
                    );

                    chosenGameObject = obj;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("View", true)) {
            ImGui::Checkbox("Wireframe Mode", &wireframeMode);
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Window", false)) {
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    void duplicate() {
        if(chosenGameObject == nullptr) return;

        SteelObject* obj = chosenGameObject->duplicate();
        Scene::currentScene->addObject(obj);

        chosenGameObject = obj;
    }
    void render_object_list() {
        if(Scene::currentScene != nullptr) {
            ImGui::Begin("Object list");

            ImGui::BeginListBox("##");

            for(auto object : scene.objects) {
                std::stringstream label;
                label << object->name << " (0x" << (unsigned long)object << ")";
                std::string _label = label.str();
                if(ImGui::Selectable(_label.c_str(), chosenGameObject == object)) {
                    chosenGameObject = object;
                }
            }

            ImGui::EndListBox();

            ImGui::End();
        }
    }
    void render_ui(double time) {
        imgui_newframe();

        render_main_bar();

        render_object_list();

        Transform* objtrans = &chosenGameObject->transform;
        
        ImGui::Begin("Statistics");
    
        ImGui::Text("FPS: %f", 1 / time);
        ImGui::Text("Delta: %fms", time * 1000);

        ImGui::End();

        draw_object_info(chosenGameObject);

        draw_mesh_renderer(chosenGameObject);

        ImGui::Begin("Rendering info");
        if(Scene::currentScene != nullptr) {
            ImGui::Text("Vertices: %d", allVertices);
            ImGui::Text("Faces: %d", allFaces);
        }
        ImGui::End();

        draw_camera_info(editorCamera, cameraSpeed);

        imgui_render();
    }
    void render(double time) override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(Scene::currentScene == nullptr && !loaded) {
            std::cerr << "No scene loaded" << std::endl;
            stop(1);
            return;
        }

        Scene::currentScene->tick();

        render_ui(time);

        set_debug_color(glm::vec3(1));

        if(chosenGameObject != nullptr) {
            auto mr = chosenGameObject->getComponent<MeshRenderer>();
            glm::vec3 minBound = mr->mesh->findMinBoundWithModel(chosenGameObject->transform.modelMatrix());
            glm::vec3 maxBound = mr->mesh->findMaxBoundWithModel(chosenGameObject->transform.modelMatrix());

            glm::vec3 center = (minBound + maxBound) / 2.0f;

            float x_sc = maxBound.x - minBound.x;
            float y_sc = maxBound.y - minBound.y;
            float z_sc = maxBound.z - minBound.z;

            draw_wire_cube(center, glm::vec3(x_sc, y_sc, z_sc));
        }

        check_wireframe();
        swapBuffers();
        BaseApplication::render(time);
    }
    void onEnd() override {
        BaseApplication::onEnd();
    }
    void onResize(GLFWwindow* window, int width, int height) override {
        BaseApplication::onResize(window, width, height);

        sprintf(title, "Steel Engine | %dx%d | OGL %s", Width, Height, glGetString(GL_VERSION));
        updateTitle();
    }
    void onKeyCallback(int k, int sc, int a, int m) override {
        if(k == GLFW_KEY_DELETE && a == GLFW_PRESS) {
            if(chosenGameObject != nullptr) {
                scene.removeObject(chosenGameObject);
                chosenGameObject = nullptr;
            }
        }
        if(k == GLFW_KEY_D && a == GLFW_PRESS && m == GLFW_MOD_CONTROL) {
            duplicate();
        }
        if(k == GLFW_KEY_D && a == GLFW_PRESS && m == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
            chosenGameObject = nullptr;
    }
    void onMouseButtonCallback(int k, int a, int m) override {
        BaseApplication::onMouseButtonCallback(k, a, m);
    }
    void onMouseCursorCallback(double xpos, double ypos) override {
        BaseApplication::onMouseCursorCallback(xpos, ypos);

        if(MoveArrow::instance != nullptr && chosenGameObject != nullptr) {
            Ray ray = editorCamera.rayFromCameraScreenSpace(glm::vec2(xpos, ypos));

            set_debug_color(glm::vec3(1, 0, 0));
            draw_line(ray.origin, ray.direction);

            MoveArrow::instance->x_highlight = 
                MoveArrow::instance->XBB(
                    chosenGameObject->transform.position, 
                    ray.origin, ray.direction
                );
        }
    }
    void onMouseWheelCallback(double xoffset, double yoffset) override {
        if(getMouseButton(1)) {
            cameraSpeed *= 1 + yoffset * 0.1;
            cameraSpeed = cameraSpeed < 0.01f ? 0.01 : (cameraSpeed > 100 ? 100 : cameraSpeed);
        }
        BaseApplication::onMouseWheelCallback(xoffset, yoffset);
    }
};
