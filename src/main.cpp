#include <iostream>
#include "steel.hpp"

Camera* Camera::currentCamera = nullptr;
BaseApplication* BaseApplication::instance = nullptr;
Scene* Scene::currentScene = nullptr;
Screen* Screen::instance = nullptr;
MoveArrow* MoveArrow::instance = nullptr;

int main() {
    srand(time(NULL));
    SteelMain steel(1920, 1080);

    steel.run();
    return 0;
}