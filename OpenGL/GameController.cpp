#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h" // Directly include the tool window
#include "Font.h"

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Black background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(0));

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({0, 0, 8}, { 0, 0, 0 }, { 0, 1, 0 });
}

void GameController::RunGame()
{
    // Directly create and show the tool window
    OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
    toolWindow->Show();

    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

    // Load the light sphere
    Mesh* lightSphere = new Mesh();
    lightSphere->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    lightSphere->SetPosition({ 0, 0, 4 });  // Initial position
    lightSphere->SetScale({ 0.1, 0.1, 0.1 }); // Smaller light sphere
    lightSphere->SetColor({ 1.0f, 1.0f, 1.0f }); // White color
    lights.push_back(lightSphere);

    // Load Suzanne 
    Mesh* suzanne = new Mesh();
    suzanne->Create(&shaderDiffuse, "../Assets/Models/Suzanne.obj");
    suzanne->SetPosition({ 0, 0, 0 });  
    suzanne->SetScale({ 1.0, 1.0, 1.0 });
    meshBoxes.push_back(suzanne);
    


    /*Font* arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);*/

    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    do
    {
        System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer

        // Retrieve slider values
        float specularStrength = toolWindow->GetSpecularStrengthSliderValue();
        glm::vec3 specularColor = glm::vec3(
            toolWindow->GetSpecularColorRSliderValue(),
            toolWindow->GetSpecularColorGSliderValue(),
            toolWindow->GetSpecularColorBSliderValue()
        );

        // Update shader uniforms
        shaderDiffuse.SetFloat("material.specularStrength", specularStrength);
        shaderDiffuse.SetVec3("light[0].specularColor", specularColor);




        for (auto light : lights)
        {
            light->Render(camera.GetProjection() * camera.GetView());
        }

        glm::vec3 rotationSpeed = { 0.0f, 0.000f, 0.0f };
        for (auto box : meshBoxes)
        {
            box->SetRotation(box->GetRotation() + rotationSpeed);
            box->Render(camera.GetProjection() * camera.GetView());
        }

        //arialFont->RenderText("Hello World", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });



        glfwSwapBuffers(win); // Swap the front and back buffers
        glfwPollEvents();


    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0); // Check if the window was closed

    for (auto light : lights)
    {
        light->Cleanup();
        delete light;
    }
    lights.clear();

    for (auto box : meshBoxes)
    {
        box->Cleanup();
        delete box;
    }
    meshBoxes.clear();

    shaderFont.Cleanup();
    shaderDiffuse.Cleanup();
    shaderColor.Cleanup();
}
