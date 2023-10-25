#include "ui.hpp"

#include "../core/mesh.hpp"
#include "../core/steel_imgui.hpp"
#include "camera.hpp"
#include "arrows.hpp"

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
