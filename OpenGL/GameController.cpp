#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

//Removed Constructor

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
    glEnable(GL_CULL_FACE);

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 100, 100, 100 }, { 0, 0, 0 }, { 0, 1, 0 });


}

void GameController::RunGame()
{
    // Show the C++/CLI tool window
    OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
    window->Show();

    shader = Shader();
    shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    mesh = Mesh();
    mesh.Create(&shader);

    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    do
    {
        System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events

        
        GLint yLoc = glGetUniformLocation(shader.GetProgramID(), "YValue");
        glUniform1f(yLoc, OpenGL::ToolWindow::YValue);

        GLint uLoc = glGetUniformLocation(shader.GetProgramID(), "UValue");
        glUniform1f(uLoc, OpenGL::ToolWindow::UValue);

        GLint vLoc = glGetUniformLocation(shader.GetProgramID(), "VValue");
        glUniform1f(vLoc, OpenGL::ToolWindow::VValue);
        
        GLint invertLoc = glGetUniformLocation(shader.GetProgramID(), "InvertColors");
        glUniform1i(invertLoc, OpenGL::ToolWindow::InvertColors ? 1 : 0);






        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
        mesh.Render(camera.GetProjection() * camera.GetView());
        glfwSwapBuffers(win);  // Swap the front and back buffers
        glfwPollEvents();
    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);  // Check if the ESC key was pressed and if the window was closed

    mesh.Cleanup();
    shader.Cleanup();
}






