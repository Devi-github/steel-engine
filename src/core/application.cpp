#include "application.hpp"
#include "steel_imgui.hpp"
#include "screen.hpp"

#include <GL/glew.h>
#include <iostream>

BaseApplication::BaseApplication(int w, int h, const char* title) {
    BaseApplication::instance = this;

    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    //glfwWindowHint(GL_MULTISAMPLE, 8);

    Screen::instance = new Screen();
    Screen::instance->width = w;
    Screen::instance->height = h;

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

    totalTimeElapsed = 0.0;

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

    auto mouseWheelCall = [](GLFWwindow* w, double xoff, double yoff) {
        static_cast<BaseApplication*>(glfwGetWindowUserPointer(w))->onMouseWheelCallback(xoff, yoff);
    };
    glfwSetScrollCallback(window, mouseWheelCall);

    initialize_imgui(window);
}
double BaseApplication::getTime() {
    return glfwGetTime();
}
void BaseApplication::init() {
    glEnable(GL_MULTISAMPLE);

    glfwSetWindowTitle(window, title);
}
void BaseApplication::update(double time) {
    glfwGetCursorPos(window, &mouseX, &mouseY);

    deltaMouseX = mouseX - prevMouseX;
    deltaMouseY = mouseY - prevMouseY;
    
    prevMouseX = mouseX;
    prevMouseY = mouseY;

    currentDelay -= time;

    glfwPollEvents();
}
void BaseApplication::onKeyCallback(int key, int scancode, int action, int mods) {

}
void BaseApplication::onMouseButtonCallback(int key, int action, int mods) {
    
}
void BaseApplication::onMouseCursorCallback(double xpos, double ypos) {
    
}
void BaseApplication::onMouseWheelCallback(double xoffset, double yoffset)
{
    
}
int BaseApplication::run()
{
    init();
    glfwSetTime(0);
    double time = 0;
    double delta = 0; // Small amount, so that divide by zero won't happen

    while(!glfwWindowShouldClose(window)) {
        render(delta);
        time = glfwGetTime();
        update(delta);
        delta = glfwGetTime() - time;
        time = glfwGetTime();
        totalTimeElapsed = time;
    }
    onEnd();
    return exitCode;
}

BaseApplication &BaseApplication::getInstance()
{
    return *BaseApplication::instance;
}

void BaseApplication::setCursorMode(int mode)
{
    glfwSetInputMode(window, GLFW_CURSOR, mode);
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

void BaseApplication::updateTitle()
{
    if(currentDelay > 0) return;

    glfwSetWindowTitle(window, title);
    currentDelay = setTitleDelay;
}

void BaseApplication::setVsync(int interval) {
    glfwSwapInterval(interval);
}

void BaseApplication::stop(int exitCode) {
    glfwSetWindowShouldClose(window, 1);
    this->exitCode = exitCode;
}

void BaseApplication::onResize(GLFWwindow* w, int wid, int hei) {
    glViewport(0, 0, wid, hei);
    Width = wid;
    Height = hei;
}
