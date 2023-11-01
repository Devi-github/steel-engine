#pragma once

#include "../core/object.hpp"
#include "../core/scene_manager.hpp"
#include "camera.hpp"

void draw_mesh_renderer(SteelObject* chosenGameObject);
void draw_camera_info(Camera &editorCamera, float& cameraSpeed);
void draw_object_info(SteelObject* object);
void draw_object_create_menu(Scene& scene, SteelObject* &chosenGameObject);
void draw_main_bar(Scene& scene, SteelObject* &chosenGameObject, bool& exitPolled, bool* wireframeMode);
void draw_object_list(Scene &scene, SteelObject* &chosenGameObject);
