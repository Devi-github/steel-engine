#pragma once

#include "../core/object.hpp"
#include "camera.hpp"

void draw_mesh_renderer(SteelObject* chosenGameObject);
void draw_camera_info(Camera &editorCamera, float& cameraSpeed);
void draw_object_info(SteelObject* object);
