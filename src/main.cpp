#include <iostream>
#include "steel.hpp"

Camera* Camera::currentCamera = nullptr;
BaseApplication* BaseApplication::instance = nullptr;

int main() {
    SteelMain steel(1366, 768);

    steel.run();
    return 0;
}