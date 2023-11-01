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

    double totalTimeElapsed;

protected:
    virtual void update(double time);

    virtual void render(double time);
    virtual void init();

    virtual void onResize(GLFWwindow*, int width, int height);
    virtual void onEnd();

    virtual void onKeyCallback(int key, int scancode, int action, int mods);

    virtual void onMouseButtonCallback(int key, int action, int mods);

    virtual void onMouseCursorCallback(double xpos, double ypos);

    virtual void onMouseWheelCallback(double xoffset, double yoffset);

    void swapBuffers();

    bool getKey(int key);

    bool getMouseButton(int key);

    void updateTitle();

    void setVsync(int);
    
    bool wireframeMode = false;
    bool exitPolled = false;

    double mouseX, mouseY;
    double deltaMouseX, deltaMouseY;

    char title[200]; // Max 200 characters
private:
    GLFWwindow* window;

    double currentDelay = 0;
    double setTitleDelay = 0.1;

    int exitCode = 0;
    double prevMouseX, prevMouseY;
};
