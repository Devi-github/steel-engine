#include "application.hpp"
#include "steel_imgui.hpp"
#include <GL/glew.h>
#include <iostream>

BaseApplication::BaseApplication(int w, int h, const char* title) {
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GL_MULTISAMPLE, 8);

    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if(!window) {
        std::cerr << "Failed to create a window!" << std::endl;
        return;
    }
    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew!" << std::endl;
        return;
    }

    Width = w;
    Height = h;

    glfwSetWindowUserPointer(window, this);
    auto resize = [](GLFWwindow* w, int wid, int hei) {
        static_cast<BaseApplication*>(glfwGetWindowUserPointer(w))->onResize(w, wid, hei);
    };
    glfwSetWindowSizeCallback(window, resize);

    auto keyCall = [](GLFWwindow* w, int k, int sc, int a, int m) {
        static_cast<BaseApplication*>(glfwGetWindowUserPointer(w))->onKeyCallback(k, sc, a, m);
    };
    glfwSetKeyCallback(window, keyCall);

    auto mouseKeyCall = [](GLFWwindow* w, int k, int a, int m) {
        static_cast<BaseApplication*>(glfwGetWindowUserPointer(w))->onMouseButtonCallback(k, a, m);
    };
    glfwSetMouseButtonCallback(window, mouseKeyCall);

    auto mouseCursorCall = [](GLFWwindow* w, double xpos, double ypos) {
        static_cast<BaseApplication*>(glfwGetWindowUserPointer(w))->onMouseCursorCallback(xpos, ypos);
    };
    glfwSetCursorPosCallback(window, mouseCursorCall);

    initialize_imgui(window);
}
double BaseApplication::getTime() {
    return glfwGetTime();
}
void BaseApplication::init() {

}
void BaseApplication::update(double time) {
    glfwPollEvents();
}
void BaseApplication::run() {
    init();
    glfwSetTime(0);
    double time = 0;
    double renderDelta = 0.01; // Small amount, so that divide by zero won't happen
    double updateDelta = 0.01; // Small amount, so that divide by zero won't happen
    while(!glfwWindowShouldClose(window)) {
        render(renderDelta);
        renderDelta = glfwGetTime() - time;
        time = glfwGetTime();
        update(updateDelta);
        updateDelta = glfwGetTime() - time;
        time = glfwGetTime();
    }
    onEnd();
}

void BaseApplication::render(double time) {
    
}

void BaseApplication::swapBuffers() {
    glfwSwapBuffers(window);
}

void BaseApplication::onEnd() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
bool BaseApplication::getKey(int key) {
    return glfwGetKey(window, key);
}

bool BaseApplication::getMouseButton(int key) {
    return glfwGetMouseButton(window, key);
}

void BaseApplication::stop() {
    glfwSetWindowShouldClose(window, 1);
}

void BaseApplication::onResize(GLFWwindow* w, int wid, int hei) {
    glViewport(0, 0, wid, hei);
}
