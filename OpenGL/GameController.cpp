#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include <iostream> // For printing cube count

void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Initialize the window
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");    // Initialize GLEW
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);              // Enable capturing the escape key
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);                            // Black background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    srand(time(0));

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0, 0, 8 }, { 0, 0, 0 }, { 0, 1, 0 });



    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

    shaderColorByPosition = Shader(); 
    shaderColorByPosition.LoadShaders("ColorByPosition.vertexshader", "ColorByPosition.fragmentshader");


    // Initialize the light sphere for "Move Light"
    lightSphere = new Mesh();
    lightSphere->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    lightSphere->SetPosition({ 0, 0, 4 });
    lightSphere->SetScale({ 0.1, 0.1, 0.1 });
    lightSphere->SetColor({ 1.0f, 1.0f, 1.0f });
    lights.push_back(lightSphere);

    // Initialize Suzanne model for "Move Light"
    suzanne = new Mesh();
    suzanne->Create(&shaderDiffuse, "../Assets/Models/Suzanne.obj");
    suzanne->SetPosition({ 0, 0, 0 });
    suzanne->SetScale({ 1.0, 1.0, 1.0 });
    meshBoxes.push_back(suzanne);



    // Initialize the textured sphere for "Move Cubes to Sphere"
    sphere = new Mesh();
    sphere->Create(&shaderDiffuse, "../Assets/Models/Sphere_Suzanne_tex.obj");
    sphere->SetPosition({ 0, 0, 0 });
    sphere->SetScale({ 1.0, 1.0, 1.0 });


    arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);
}

void GameController::RunGame()
{
    OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
    toolWindow->Show();
    toolWindow->BringToFront();
    toolWindow->TopMost = true; // Always keep the tool window on top

    



    GLFWwindow* win = WindowController::GetInstance().GetWindow();

    do
    {
        //Resolution currentResolution = WindowController::GetInstance().GetResolution();

        System::Windows::Forms::Application::DoEvents(); // Handle Windows form events
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Check which radio button is selected
        if (toolWindow->radioButtonMoveLight->Checked)
        {
            HandleMoveLight();

            // Check if Reset Light Position button is clicked
            if (toolWindow->ResetLightButtonClicked)
            {
                ResetPositions(); // Call ResetLightPosition logic
                toolWindow->ResetLightButtonClicked = false; // Reset the flag
            }
        }
        else if (toolWindow->radioButtonMoveCubes->Checked)
        {
            HandleMoveCubesToSphere(win);
        }

        else if (toolWindow->radioButtonColorByPosition->Checked)
        {
            Resolution currentResolution = WindowController::GetInstance().GetResolution();
            HandleColorByPosition(win, currentResolution); 


            if (toolWindow->ResetButtonClicked)
            {
                ResetPositions(); 
                toolWindow->ResetButtonClicked = false; 
            }
        }

        glfwSwapBuffers(win);
        glfwPollEvents();

    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);

    Cleanup();
}

// Handles the "Move Light" functionality
void GameController::HandleMoveLight()
{
    glUseProgram(shaderDiffuse.GetProgramID());

    GLint useColorByPositionLoc = glGetUniformLocation(shaderDiffuse.GetProgramID(), "useColorByPosition");
    glUniform1i(useColorByPositionLoc, false);

    GLint specularStrengthLoc = glGetUniformLocation(shaderDiffuse.GetProgramID(), "material.specularStrength");
    glUniform1f(specularStrengthLoc, OpenGL::ToolWindow::SpecularStrengthValue);

    GLint specularColorLoc = glGetUniformLocation(shaderDiffuse.GetProgramID(), "light[0].specularColor");
    glUniform3f(
        specularColorLoc,
        OpenGL::ToolWindow::SpecularColorRValue,
        OpenGL::ToolWindow::SpecularColorGValue,
        OpenGL::ToolWindow::SpecularColorBValue
    );
    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    Resolution currentResolution = WindowController::GetInstance().GetResolution();

    if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(win, &mouseX, &mouseY);

        float centerX = static_cast<float>(currentResolution.width) / 2.0f;
        float centerY = static_cast<float>(currentResolution.height) / 2.0f;

        float relativeX = static_cast<float>(mouseX - centerX);
        float relativeY = static_cast<float>(centerY - mouseY); 

        glm::vec3 direction(relativeX, relativeY, 0.0f);

        if (glm::length(direction) > 0.0f)
        {
            direction = glm::normalize(direction);
        }

        float distanceFromCenter = glm::length(glm::vec2(relativeX, relativeY));
        float speed = distanceFromCenter * 0.0001f; 

        glm::vec3 newPosition = lightSphere->GetPosition() + (direction * speed);

        lightSphere->SetPosition(newPosition);
    }

    lightSphere->Render(camera.GetProjection() * camera.GetView());

    glm::vec3 rotationSpeed = { 0.0f, 0.000f, 0.0f };
    suzanne->SetRotation(suzanne->GetRotation() + rotationSpeed);
    suzanne->Render(camera.GetProjection() * camera.GetView());
}



// Handles the "Move Cubes to Sphere" functionality
void GameController::HandleMoveCubesToSphere(GLFWwindow* win)
{
    glUseProgram(shaderDiffuse.GetProgramID());

    GLint useColorByPositionLoc = glGetUniformLocation(shaderDiffuse.GetProgramID(), "useColorByPosition");
    glUniform1i(useColorByPositionLoc, false);

    sphere->Render(camera.GetProjection() * camera.GetView());

    if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        SpawnCube();
    }

    for (int i = cubes.size() - 1; i >= 0; --i)
    {
        Mesh* cube = cubes[i];
        glm::vec3 direction = glm::normalize(sphere->GetPosition() - cube->GetPosition());
        cube->SetPosition(cube->GetPosition() + direction * 0.01f);

        if (glm::length(cube->GetPosition() - sphere->GetPosition()) < 0.1f)
        {
            cube->Cleanup();
            delete cube;
            cubes.erase(cubes.begin() + i);
        }
    }

    for (auto cube : cubes)
    {
        cube->Render(camera.GetProjection() * camera.GetView());
    }

    RenderCubeCount();
}

// Spawns a cube at a random position around the sphere
void GameController::SpawnCube()
{
    Mesh* cube = new Mesh();
    cube->Create(&shaderDiffuse, "../Assets/Models/Cube.obj");

    float x = (rand() % 200 - 100) / 10.0f; 
    float y = (rand() % 200 - 100) / 10.0f; 
    float z = (rand() % 200 - 100) / 10.0f; 

    cube->SetPosition({ x, y, z });
    cube->SetScale({ 0.5f, 0.5f, 0.5f });
    cubes.push_back(cube);
}

void GameController::RenderCubeCount()
{
    
    std::string cubeText = "Cubes Rendered: " + std::to_string(cubes.size());


    if (arialFont != nullptr)
    {
        arialFont->RenderText(cubeText, 10, 50, 0.5f, { 1.0f, 1.0f, 0.0f }); 
    }
}

// Cleans up resources
void GameController::Cleanup()
{
    sphere->Cleanup();
    delete sphere;

    for (auto cube : cubes)
    {
        cube->Cleanup();
        delete cube;
    }
    cubes.clear();

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


    shaderColor.Cleanup();
    shaderDiffuse.Cleanup();
    shaderFont.Cleanup();   
    shaderColorByPosition.Cleanup();

}

void GameController::HandleColorByPosition(GLFWwindow* win, const Resolution& currentResolution)
{
    glUseProgram(shaderDiffuse.GetProgramID());

    GLint useColorByPositionLoc = glGetUniformLocation(shaderDiffuse.GetProgramID(), "useColorByPosition");
    glUniform1i(useColorByPositionLoc, true);

    suzanne->Render(camera.GetProjection() * camera.GetView());

    

    lightSphere->Render(camera.GetProjection() * camera.GetView()); 

    if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {

        double mouseX, mouseY;
        glfwGetCursorPos(win, &mouseX, &mouseY);

        float centerX = static_cast<float>(currentResolution.width) / 2.0f;
        float centerY = static_cast<float>(currentResolution.height) / 2.0f;

        float relativeX = static_cast<float>(mouseX - centerX);
        float relativeY = static_cast<float>(centerY - mouseY); 

        glm::vec3 direction(relativeX, relativeY, 0.0f);

       
        if (glm::length(direction) > 0.0f)
        {
            direction = glm::normalize(direction);
        }

        
        float distanceFromCenter = glm::length(glm::vec2(relativeX, relativeY));
        float speed = distanceFromCenter * 0.0001f; 

        glm::vec3 newPosition = suzanne->GetPosition() + (direction * speed);

        suzanne->SetPosition(newPosition);
    }
}

void GameController::ResetPositions()
{

    camera.LookAt({ 0, 0, 8 }, { 0, 0, 0 }, { 0, 1, 0 });


    lightSphere->SetPosition({ 0, 0, 4 });
    lightSphere->SetScale({ 0.1f, 0.1f, 0.1f }); 
    
    suzanne->SetPosition({ 0, 0, 0 });
    suzanne->SetScale({ 1.0f, 1.0f, 1.0f }); 


 
    sphere->SetPosition({ 0, 0, 0 });
    sphere->SetScale({ 0.5f, 0.5f, 0.5f });


    shaderDiffuse.SetFloat("material.specularStrength", 4.0f);
    shaderDiffuse.SetVec3("light[0].specularColor", { 3.0f, 3.0f, 3.0f }); 
}













