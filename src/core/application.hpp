#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class BaseApplication {
public:
    // Creates a glfw window
    BaseApplication(int width, int height, const char* title);
    // Runs the application
    int run();

    static BaseApplication* instance;
    static BaseApplication& getInstance();

    void setCursorMode(int mode);

    BaseApplication(BaseApplication& other) = delete;
    void operator=(const BaseApplication&) = delete;

    double getTime();
    // Stops the application
    void stop(int exitCode = 0);
public:
    int Width, Height;

protected:
    virtual void update(double time);

    virtual void render(double time);
    virtual void init();

    virtual void onResize(GLFWwindow*, int width, int height);
    virtual void onEnd();

    virtual void onKeyCallback(int key, int scancode, int action, int mods) = 0;

    virtual void onMouseButtonCallback(int key, int action, int mods) = 0;

    virtual void onMouseCursorCallback(double xpos, double ypos);

    void swapBuffers();

    bool getKey(int key);

    bool getMouseButton(int key);
    
    bool wireframeMode = false;

    double mouseX, mouseY;
    double deltaMouseX, deltaMouseY;
private:
    GLFWwindow* window;

    int exitCode = 0;
    double prevMouseX, prevMouseY;
};
