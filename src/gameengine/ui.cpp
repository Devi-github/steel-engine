#include "ui.hpp"

#include "../core/mesh.hpp"
#include "../core/steel_imgui.hpp"
#include "primitives.hpp"
#include "camera.hpp"
#include "arrows.hpp"
#include "functions.hpp"

#include <glm/glm.hpp>

static void draw_material_property(Material* material, MaterialProperty property) {
    // TODO: Implement this method for every possible property type
    switch(property.type) {
        case GL_FLOAT:
        break;
        case GL_UNSIGNED_INT:
        break;
        case GL_INT:
        break;
        case GL_FLOAT_VEC3:
        
        //ImGui::DragFloat3(property.name, )
        break;
        case GL_FLOAT_VEC4:
        break;
        default:
        break;
    }
}

void draw_mesh_renderer(SteelObject *chosenGameObject) {
    if(!ImGui::Begin("Mesh renderer"))
        return;
    if(chosenGameObject != nullptr) {
        MeshRenderer* mr = chosenGameObject->getComponent<MeshRenderer>();
        if(mr != nullptr) {
            ImGui::Text("Mesh renderer found at %p", mr);
            ImGui::Text("VBO: %u VAO: %u EBO: %u", mr->mesh->vbo, mr->mesh->vao, mr->mesh->ebo);
            ImGui::Text("Mesh renderer mesh is at: %p", mr->mesh);
            ImGui::Text("Mesh vertex buffer is at: %p", mr->mesh->vertexBuffer);
            ImGui::Text("Mesh element buffer is at: %p", mr->mesh->indices);
            ImGui::Text("Vertices: %d", mr->mesh->vertexCount);
            ImGui::Text("Material is at: %p", mr->material);
            ImGui::Text("Shared material is at: %p", mr->sharedMaterial);

            
        } else {
            ImGui::Text("No mesh renderer component found!");
        }
    }
    ImGui::End();
}

void draw_camera_info(Camera &editorCamera, float &cameraSpeed)
{
    if(!ImGui::Begin("Camera")) return;

    if(Camera::currentCamera != nullptr) {
        ImGui::Text("Position: X: %f Y: %f Z: %f", editorCamera.transform.position.x, 
            editorCamera.transform.position.y, editorCamera.transform.position.z);
        ImGui::Text("Look Direction: X: %f Y: %f Z: %f", editorCamera.transform.forward().x, 
            editorCamera.transform.forward().y, editorCamera.transform.forward().z);
        ImGui::DragFloat("Camera Speed", &cameraSpeed, 0.05f, 0.02f, 100.0f);
    }
    ImGui::End();
}

void draw_object_info(SteelObject *object)
{
    if(!ImGui::Begin("Object information")) return;

    if(object != nullptr) {
        ImGui::InputText("Name", object->name.data(), 128); // FIXME: Create custom method for this, because SIGSEGV

        ImGui::DragFloat3("Position", (float*)&object->transform.position, 0.1f);
        ImGui::DragFloat3("Rotation", (float*)&object->transform.rotation, 0.05f);
        ImGui::DragFloat3("Scale", (float*)&object->transform.scale, 0.1f);

        draw_move_arrows(object->transform.position);
    }
    
    ImGui::End();
}

void draw_create_primitive_menu(Scene& scene, SteelObject* &chosenGameObject) {
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

void draw_object_create_menu(Scene& scene, SteelObject* &chosenGameObject)
{
    if(ImGui::BeginMenu("SteelObject")) {
        draw_create_primitive_menu(scene, chosenGameObject);
    }
}

void draw_main_bar(Scene &scene, SteelObject *&chosenGameObject, bool& exitPolled, bool *wireframeMode)
{
    ImGui::BeginMainMenuBar();

    if(ImGui::BeginMenu("File")) {
        if(ImGui::MenuItem("New Scene", "", false, false)) {
            std::cout << "New Scene is not yet implemented" << std::endl;
        }
        if(ImGui::MenuItem("Exit", "ALT+F4")) {
            exitPolled = true;
        }
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Edit")) {
        if(ImGui::MenuItem("Deselect", "CTRL+SHIFT+D", false, chosenGameObject != nullptr)) {
            chosenGameObject = nullptr;
        }
        if(ImGui::MenuItem("Duplicate", "CTRL+D", false, chosenGameObject != nullptr)) {
            chosenGameObject = duplicate(scene, chosenGameObject);
        }
        ImGui::EndMenu();
    }
    draw_object_create_menu(scene, chosenGameObject);
    
    if(ImGui::BeginMenu("View", true)) {
        ImGui::Checkbox("Wireframe Mode", wireframeMode);
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Window", false)) {
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}

void draw_object_list(Scene &scene, SteelObject* &chosenGameObject)
{
    if(Scene::currentScene == nullptr) return;
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
