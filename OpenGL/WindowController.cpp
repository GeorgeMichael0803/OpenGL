#include "WindowController.h"

WindowController::WindowController()
{
    window = nullptr;
}

WindowController::~WindowController()
{
    if (window != nullptr)
    {
        glfwTerminate();
        window = nullptr;
    }
}

void WindowController::NewWindow()
{
    M_ASSERT(glfwInit(), "Failed to initialize GLFW."); // Initialize GLFW

    // Get the primary monitor and its video mode (desktop resolution)
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    // Open a window and create its OpenGL context with desktop resolution
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    M_ASSERT((window = glfwCreateWindow(mode->width, mode->height, "A sample scene", NULL, NULL)) != nullptr, "Failed to open GLFW window.");
    glfwMakeContextCurrent(window);
}


Resolution WindowController::GetResolution()
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return Resolution(mode->width, mode->height);
}

