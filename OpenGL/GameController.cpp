#include "GameController.h"
#include "WindowController.h"
#ifdef USE_TOOL_WINDOW
#include "ToolWindow.h"
#endif
#include "Font.h"
#include "GameTime.h"


void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    srand(time(0));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


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

    /*shaderSkybox = Shader();
    shaderSkybox.LoadShaders("SkyBox.vertexshader", "SkyBox.fragmentshader");*/

    shaderPost = Shader();
    shaderPost.LoadShaders("PostProcessor.vertexshader", "PostProcessor.fragmentshader");


    #pragma region Post Processes
    postProcessor = PostProcessor();
    postProcessor.Create(&shaderPost);
    #pragma endregion



#pragma region Model Setup

    #pragma region Light
    Mesh* light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 3.0f, 0.0f, 1.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);
    #pragma endregion


    Mesh* mesh = nullptr;
    #pragma region Cube (Commented out)
    mesh = new Mesh();
    mesh->Create(&shaderDiffuse, "../Assets/Models/Cube.obj", 1000);
    mesh->SetCameraPosition(camera.GetPosition());
    mesh->SetScale({ 0.1f, 0.1f, 0.1f });
    mesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    meshes.push_back(mesh);
    #pragma endregion


    #pragma region Fighter
    /*
    mesh = new Mesh();
    mesh->Create(&shaderDiffuse, "../Assets/Models/Fighter.obj");
    mesh->SetCameraPosition(camera.GetPosition());
    mesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    mesh->SetScale({ 0.0002f, 0.0002f, 0.0002f });
    meshes.push_back(mesh);*/
    #pragma endregion

#pragma endregion

#pragma region Skybox Setup
    /*skybox = new Skybox();
    skybox->Create(&shaderSkybox, "../Assets/Models/Skybox.obj",
        {
            "../Assets/Textures/Skybox/right.jpg",
            "../Assets/Textures/Skybox/left.jpg",
            "../Assets/Textures/Skybox/top.jpg",
            "../Assets/Textures/Skybox/bottom.jpg",
            "../Assets/Textures/Skybox/front.jpg",
            "../Assets/Textures/Skybox/back.jpg"
        });*/
#pragma endregion



    Font* arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);

#pragma region Multiple lights and boxes commented out
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



    GameTime::GetInstance().Initialize();
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

        GameTime::GetInstance().Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer

        /*camera.Rotate();
        glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
        skybox->Render(camera.GetProjection() * view);*/

        postProcessor.Start();

        for (auto light : lights)
        {
            light->Render(camera.GetProjection() * camera.GetView());
        }

        // Note we are now using a pointer so we are not doing a shallow copy , we could also use a reference if we were not on the heap
        glm::vec3 rotationSpeed = { 0.0f, 1.0f, 0.0f };
        for (auto mesh : meshes)
        {
            mesh->SetRotation(mesh->GetRotation() + (rotationSpeed * (float)GameTime::GetInstance().DeltaTime()));
            mesh->Render(camera.GetProjection() * camera.GetView());

        }


        postProcessor.End();
        arialFont->RenderText(std::to_string(GameTime::GetInstance().Fps()), 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });

        glfwSwapBuffers(win); // Swap the front and back buffers
        glfwPollEvents();

    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0); // Check if the window was closed

    postProcessor.Cleanup();

    for (auto light : lights)
    {
        light->Cleanup();
        delete light;
    }
    lights.clear(); // Why not

    for (auto box : meshes)
    {
        box->Cleanup();
        delete box;
    }
    meshes.clear(); // Why not

    //skybox->Cleanup();
    //delete skybox;

    shaderPost.Cleanup();
    shaderFont.Cleanup();
    shaderDiffuse.Cleanup();
    shaderColor.Cleanup();

}







