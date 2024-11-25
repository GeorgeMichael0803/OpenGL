#include "GameController.h"
#include "WindowController.h"
#ifdef USE_TOOL_WINDOW
#include "ToolWindow.h"
#endif
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
    camera.LookAt({ 5, 5, 5 }, { 0, 0, 0 }, { 0, 1, 0 });


}

void GameController::RunGame()
{
#ifdef USE_TOOL_WINDOW
    // Show the C++/CLI tool window
    OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
    window->Show();
#endif

    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");


    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 3.0f, 1.0f, 0.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);

    Mesh* box = new Mesh();
    box->Create(&shaderDiffuse, "../Assets/Models/Cube.obj");
    box->SetCameraPosition(camera.GetPosition());
    box->SetScale({ 1.0f, 1.0f, 1.0f });
    box->SetPosition({ 0.0f, 0.0f, 0.0f });
    meshBoxes.push_back(box);


    //Mesh* box = new Mesh();
    //box->Create(&shaderDiffuse, "../Assets/Models/Suzanne.obj");
    //box->SetCameraPosition(camera.GetPosition());
    //box->SetScale({ 1.0f, 1.0f, 1.0f });
    //box->SetPosition({ 0.0f, 0.0f, 0.0f });
    //meshBoxes.push_back(box);

    Font* arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);



#pragma region Multiple Lights and Multiple Meshes (Commented out)
    //// Create Lights
    //for (int i = 0; i < 4; i++)
    //{
    //    Mesh* light = new Mesh();
    //    light->Create(&shaderColor);
    //    light->SetPosition({ 1.0f, 0.6f, -0.35f + (float)i * 0.2f });
    //    light->SetLightDirection(glm::normalize(glm::vec3({ 0.0f, 0.0f, -0.35f + (float)i * 0.2f }) - light->GetPosition()));
    //    light->SetColor({ glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f) });
    //    light->SetScale({ 0.1f, 0.1f, 0.1f });
    //    lights.push_back(light);
    //}

    //for (int row = 0; row < 10; row++)
    //{
    //    for (int col = 0; col < 10; col++)
    //    {
    //        Mesh* box = new Mesh();
    //        box->Create(&shaderDiffuse);
    //        box->SetCameraPosition(camera.GetPosition());
    //        box->SetScale({ 0.1f, 0.1f, 0.1f });
    //        box->SetPosition({ 0.0f, -0.5f + row * 0.1f, -0.5f + col * 0.1f });
    //        meshBoxes.push_back(box);
    //    }
    //}
#pragma endregion




    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    do
    {
        #pragma region Winform (ifdef USE_TOOL_WINDOW used)
        #ifdef USE_TOOL_WINDOW
                System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events

                GLint loc = 0;
                loc = glGetUniformLocation(shader.GetProgramID(), "RenderRedChannel");
                glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
                loc = glGetUniformLocation(shader.GetProgramID(), "RenderGreenChannel");
                glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
                loc = glGetUniformLocation(shader.GetProgramID(), "RenderBlueChannel");
                glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
        #endif
        #pragma endregion

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer
        for (auto light : lights)
        {
            light->Render(camera.GetProjection() * camera.GetView());
        }

        // Note we are now using a pointer so we are not doing a shallow copy , we could also use a reference if we were not on the heap
        glm::vec3 rotationSpeed = { 0.0f, 0.005f, 0.0f };
        for (auto box : meshBoxes)
        {
            box->SetRotation(box->GetRotation() + rotationSpeed);
            box->Render(camera.GetProjection() * camera.GetView());
        }

        arialFont->RenderText("Hello World", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });

        glfwSwapBuffers(win); // Swap the front and back buffers
        glfwPollEvents();

    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0); // Check if the window was closed

    for (auto light : lights)
    {
        light->Cleanup();
        delete light;
    }
    lights.clear(); // Why not 

    for (auto box : meshBoxes)
    {
        box->Cleanup();
        delete box;
    }
    meshBoxes.clear(); // Why not

    shaderFont.Cleanup();
    shaderDiffuse.Cleanup();
    shaderColor.Cleanup();

}







