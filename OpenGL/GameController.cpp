#include "GameController.h"
#include "WindowController.h"

GameController::GameController()
{
    mesh = {};
}

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
}

void GameController::RunGame()
{
    mesh = Mesh();
    mesh.Create();

    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    do
    {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
        mesh.Render();
        glfwSwapBuffers(win); // Swap the front and back buffers
        glfwPollEvents();
    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0); // Check if the ESC key was pressed // Check if the window was closed

    mesh.Cleanup();
}

