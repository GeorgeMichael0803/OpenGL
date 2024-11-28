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
    M_ASSERT(glfwInit(), "Failed to initialize GLFW."); // Initialise GLFW

    // Set GLFW window hints for multisampling and OpenGL version
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // Removes window borders for borderless fullscreen

    // Get primary monitor and its video mode for fullscreen
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    // Open a borderless fullscreen window
    M_ASSERT((window = glfwCreateWindow(mode->width, mode->height, "A sample scene", NULL, NULL)) != nullptr, "Failed to open GLFW window.");
    glfwMakeContextCurrent(window);

    // Position the borderless window to cover the entire screen
    glfwSetWindowPos(window, 0, 0);
}



Resolution WindowController::GetResolution()
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return Resolution(mode->width, mode->height);
}

