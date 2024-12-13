#include "GameController.h"
#include "WindowController.h"
#include "GameTime.h"
#include "ToolWindow.h"
#include <glm/glm.hpp>
#include <random>


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
    camera.LookAt({ 0, 0, 8 }, { 0, 0, 0 }, { 0, 1, 0 });

    shaderColor = Shader();
    shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

    shaderDiffuse = Shader();
    shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    shaderFont = Shader();
    shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

    shaderSkybox = Shader();
    shaderSkybox.LoadShaders("SkyBox.vertexshader", "SkyBox.fragmentshader");

    shaderPost = Shader();
    shaderPost.LoadShaders("PostProcessor.vertexshader", "PostProcessor.fragmentshader");


#pragma region Post Processes
    postProcessor = PostProcessor();
    postProcessor.Create(&shaderPost);
#pragma endregion



#pragma region Model Setup

#pragma region Light
    light = new Mesh();
    light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
    light->SetPosition({ 0.0f, 0.0f, 4.0f });
    light->SetColor({ 1.0f, 1.0f, 1.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });
    lights.push_back(light);
#pragma endregion


    Mesh* mesh = nullptr;
#pragma region Cube (Commented out)
    /*mesh = new Mesh();
    mesh->Create(&shaderDiffuse, "../Assets/Models/Cube.obj", 1000);
    mesh->SetCameraPosition(camera.GetPosition());
    mesh->SetScale({ 0.1f, 0.1f, 0.1f });
    mesh->SetPosition({ 0.0f, 0.0f, 0.0f });
    meshes.push_back(mesh);*/
#pragma endregion


#pragma region Fighter
    fighter = new Mesh();
    fighter->Create(&shaderDiffuse, "../Assets/Models/Fighter.ase");
    fighter->SetCameraPosition(camera.GetPosition());
    fighter->SetPosition({ 0.0f, 0.0f, 0.0f });
    fighter->SetScale({ 0.002f, 0.002f, 0.002f });
    meshes.push_back(fighter);
#pragma endregion

#pragma region fish
    fish = new Mesh();
    fish->Create(&shaderDiffuse, "../Assets/Models/fish.ase" , 100);
    fish->SetCameraPosition(camera.GetPosition());
    fish->SetPosition({ 0.5f, 0.0f, 0.0f });
    fish->SetScale({ .5f, .5f, .5f });
    meshes.push_back(fish);
#pragma endregion


    fish_water = new Mesh();
    fish_water->Create(&shaderDiffuse, "../Assets/Models/fish.ase");
    fish_water->SetCameraPosition(camera.GetPosition());
    fish_water->SetPosition({ 0.5f, 0.0f, 0.0f });
    fish_water->SetScale({ .5f, .5f, .5f });
    meshes.push_back(fish_water);

#pragma endregion


#pragma region Skybox Setup
    skybox = new Skybox();
    skybox->Create(&shaderSkybox, "../Assets/Models/Skybox.obj",
        {
            "../Assets/Textures/Skybox/right.png",
            "../Assets/Textures/Skybox/left.png",
            "../Assets/Textures/Skybox/top.png",
            "../Assets/Textures/Skybox/bottom.png",
            "../Assets/Textures/Skybox/front.png",
            "../Assets/Textures/Skybox/back.png"
        });
#pragma endregion


    //arialFont = new Font();
    //arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);

    arialFont = new Font();
    arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 24);


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
}

void GameController::RunGame()
{

    // Show the C++/CLI tool window
    OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
    window->TopMost = true;
    window->Show();


    bool wasSpaceSceneChecked = false;
    bool wasMoveLightChecked = false;
    bool wasTransformChecked = false;
    bool wasWaterSceneChecked = false;


    GameTime::GetInstance().Initialize();
    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    do
    {
        GameTime::GetInstance().Update();


        System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer




        // Check if Space Scene was just selected
        if (window->SpaceScene->Checked && !wasSpaceSceneChecked)
        {
            Reset();
            wasSpaceSceneChecked = true;
            wasMoveLightChecked = false;
            wasTransformChecked = false;
            wasWaterSceneChecked = false;
        }
        // Check if Move Light was just selected
        else if (window->radioButtonMoveLight->Checked && !wasMoveLightChecked)
        {
            Reset();
            wasMoveLightChecked = true;
            wasSpaceSceneChecked = false;
            wasTransformChecked = false;
            wasWaterSceneChecked = false;
        }
        // Check if Transform Scene was just selected
        else if (window->radioButtonTransform->Checked && !wasTransformChecked)
        {
            Reset();
            wasTransformChecked = true;
            wasSpaceSceneChecked = false;
            wasMoveLightChecked = false;
            wasWaterSceneChecked = false;
        }
        // Check if Water Scene was just selected
        else if (window->WaterScene->Checked && !wasWaterSceneChecked)
        {
            Reset();
            wasWaterSceneChecked = true;
            wasSpaceSceneChecked = false;
            wasMoveLightChecked = false;
            wasTransformChecked = false;
        }




        if (window->SpaceScene->Checked)
        {
            SpaceScene();
        }
        else if (window->radioButtonMoveLight->Checked)
        {

            float specularStrength = OpenGL::ToolWindow::SpecularStrengthValue;
            glm::vec3 specularColor = {
                OpenGL::ToolWindow::SpecularColorRValue,
                OpenGL::ToolWindow::SpecularColorGValue,
                OpenGL::ToolWindow::SpecularColorBValue
            };


            HandleMoveLight(specularStrength, specularColor);

            if (window->ResetLightButtonClicked)
            {
                Reset();
                window->ResetLightButtonClicked = false;
            }
        }
        else if (window->radioButtonTransform->Checked)
        {
            if (window->ResetButtonClicked)
            {
                Reset();
                window->ResetButtonClicked = false;
            }
            

            if (window->Translate->Checked)
            {
                translateChecked = true;
            }
            else
            {
                translateChecked = false;
            }

            if (window->Rotate->Checked)
            {
                rotateChecked = true;
            }
            else
            {
                rotateChecked = false;
            }

            if (window->Scale->Checked)
            {
                scaleChecked = true;
            }
            else
            {
                scaleChecked = false;
            }
            

            HandleTransform(translateChecked, rotateChecked, scaleChecked);


            
        }
        else if (window->WaterScene->Checked)
        {
            if (window->checkBox1->Checked)
            {
                wireframeChecked = true;
            }
            else
            {
                wireframeChecked = false;
            }

            if (window->checkBox2->Checked)
            {
                tintChecked = true;
            }
            else
            {
                tintChecked = false;
            }

            float frequency = static_cast<float>(window->trackBar1->Value); 

            float amplitude = static_cast<float>(window->trackBar2->Value) / 100.0f; 

            HandleWaterScene(wireframeChecked, tintChecked, frequency, amplitude);
        }


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

    skybox->Cleanup();
    //delete skybox;

    shaderPost.Cleanup();
    shaderFont.Cleanup();
    shaderDiffuse.Cleanup();
    shaderColor.Cleanup();
    shaderSkybox.Cleanup();

}







void GameController::SpaceScene()
{

        camera.Rotate();
        glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
        skybox->Render(camera.GetProjection() * view );


        fighter->Render(camera.GetProjection() * camera.GetView());

        fish->Render(camera.GetProjection() * camera.GetView());

        RenderSpaceSceneText();


}





void GameController::HandleMoveLight(float specularStrength, glm::vec3 specularColor)
{


    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    Resolution currentResolution = WindowController::GetInstance().GetResolution();

    fighter->SetSpecularStrength(specularStrength);
    fighter->SetSpecularColor(specularColor);

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

        glm::vec3 newPosition = light->GetPosition() + (direction * speed);

        light->SetPosition(newPosition);
    }

    light->Render(camera.GetProjection() * camera.GetView());

    glm::vec3 rotationSpeed = { 0.5f, 0.f, 0.0f };
    fighter->SetRotation(fighter->GetRotation() + (rotationSpeed * (float)GameTime::GetInstance().DeltaTime())) ;
    fighter->Render(camera.GetProjection() * camera.GetView());

    RenderTextGroup("Move Light Scene", fighter);

}





void GameController::HandleTransform(bool _transform, bool _rotate, bool _scale) {
    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    static double lastMouseX = 0.0, lastMouseY = 0.0;
    double mouseX, mouseY;

    glfwGetCursorPos(win, &mouseX, &mouseY);

    double deltaX = mouseX - lastMouseX;
    double deltaY = mouseY - lastMouseY;

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    bool isLeftPressed = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool isMiddlePressed = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

    if (isLeftPressed) {

        if (_transform) {
            glm::vec3 newPosition = fighter->GetPosition();
            newPosition.x += static_cast<float>(deltaX) * 0.05f; 
            newPosition.y -= static_cast<float>(deltaY) * 0.05f; 
            fighter->SetPosition(newPosition);
        }

        if (_rotate) {
            glm::vec3 newRotation = fighter->GetRotation();
            newRotation.y += static_cast<float>(deltaX) * 0.1f; 
            newRotation.x -= static_cast<float>(deltaY) * 0.1f; 
            fighter->SetRotation(newRotation);
        }


        if (_scale) {
            glm::vec3 newScale = fighter->GetScale();

            newScale.x += static_cast<float>(deltaX) * 0.00005f;
            newScale.y -= static_cast<float>(deltaY) * 0.00005f;

            newScale.x = glm::clamp(newScale.x, 0.0005f, 0.01f);
            newScale.y = glm::clamp(newScale.y, 0.0005f, 0.01f);

            fighter->SetScale(newScale);
        }

    }

    if (isMiddlePressed) {
      
        if (_transform) {
            glm::vec3 newPosition = fighter->GetPosition();
            newPosition.z += static_cast<float>(deltaY) * 0.05f; 
            fighter->SetPosition(newPosition);
        }

        if (_rotate) {
            glm::vec3 newRotation = fighter->GetRotation();
            newRotation.z += static_cast<float>(deltaY) * 0.1f; 
            fighter->SetRotation(newRotation);
        }

        if (_scale) {
            glm::vec3 newScale = fighter->GetScale();
            // Tiny increments relative to small scale
            newScale.z -= static_cast<float>(deltaY) * 0.00005f;

            // Clamp the Z-axis scaling
            newScale.z = glm::clamp(newScale.z, 0.0005f, 0.01f);

            fighter->SetScale(newScale);
        }
    }


    fighter->Render(camera.GetProjection() * camera.GetView());

    RenderTextGroup("Transform Scene", fighter);
}


void GameController::HandleWaterScene(bool _wireframe, bool tint, float frequency, float amplitude)
{
    postProcessor.SetWireframe(_wireframe);
    postProcessor.SetFrequency(frequency);
    postProcessor.SetAmplitude(amplitude);
    postProcessor.SetTintBlue(tint);

    shaderPost.SetFloat("time", GameTime::GetInstance().CurrentTime());


    //float currentTime = static_cast<float>(GameTime::GetInstance().CurrentTime());
    //postProcessor.SetTime(currentTime);

    postProcessor.Start();

    fish_water->Render(camera.GetProjection() * camera.GetView());

    RenderTextGroup("Water Scene", fish_water);

    postProcessor.End();


}



void GameController::Reset()
{
    light->SetPosition({ 0.0f, 0.0f, 4.0f });
    light->SetScale({ 0.1f, 0.1f, 0.1f });

    //fighter->SetCameraPosition(camera.GetPosition());
    fighter->SetPosition({ 0.0f, 0.0f, 0.0f });
    fighter->SetScale({ 0.002f, 0.002f, 0.002f });
    fighter->SetRotation(glm::vec3( 0.0f, 0.0f, 0.0f)); 
    fighter->SetSpecularStrength(8.0f);
    fighter->SetSpecularColor({ 3.0f, 3.0f, 3.0f });

    camera.LookAt({ 0, 0, 8 }, { 0, 0, 0 }, { 0, 1, 0 });


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}



void GameController::RenderTextGroup(const std::string& title, Mesh* mesh, bool includeScale)
{
    int line = 0;
    float scale = 0.5f;
    glm::vec3 color = { 1.0f, 1.0f, 0.0f }; 


    arialFont->RenderText("George Michael", 10.0f, 25.0f, scale, color); 

    arialFont->RenderText(title, 10.0f, 50.0f + (line++ * 20), scale, color);

    arialFont->RenderText("FPS: " + std::to_string(GameTime::GetInstance().Fps()), 10.0f, 50.0f + (line++ * 20), scale, color);

    double mouseX, mouseY;
    glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);
    arialFont->RenderText("Mouse Pos: (" + std::to_string((int)mouseX) + ", " + std::to_string((int)mouseY) + ")", 10.0f, 50.0f + (line++ * 20), scale, color);

    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    bool leftPressed = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool middlePressed = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

    arialFont->RenderText("Left Button: " + std::string(leftPressed ? "Down" : "Up"), 10.0f, 50.0f + (line++ * 20), scale, color);
    arialFont->RenderText("Middle Button: " + std::string(middlePressed ? "Down" : "Up"), 10.0f, 50.0f + (line++ * 20), scale, color);

    arialFont->RenderText("Position: (" +
        std::to_string(mesh->GetPosition().x) + ", " +
        std::to_string(mesh->GetPosition().y) + ", " +
        std::to_string(mesh->GetPosition().z) + ")", 10.0f, 50.0f + (line++ * 20), scale, color);

    arialFont->RenderText("Rotation: (" +
        std::to_string(mesh->GetRotation().x) + ", " +
        std::to_string(mesh->GetRotation().y) + ", " +
        std::to_string(mesh->GetRotation().z) + ")", 10.0f, 50.0f + (line++ * 20), scale, color);

    if (includeScale) {
        arialFont->RenderText("Scale: (" +
            std::to_string(mesh->GetScale().x) + ", " +
            std::to_string(mesh->GetScale().y) + ", " +
            std::to_string(mesh->GetScale().z) + ")", 10.0f, 50.0f + (line++ * 20), scale, color);
    }
}



void GameController::RenderSpaceSceneText()
{
    if (!arialFont)
        return;

    float scale = 0.5f;
    glm::vec3 color = { 1.0f, 1.0f, 0.0f }; 

    int line = 0; 
    float startX = 10.0f; 
    float startY = 50.0f; 

    arialFont->RenderText("George Michael", startX, startY + (line++ * 20), scale, color);

    arialFont->RenderText("FPS: " + std::to_string(GameTime::GetInstance().Fps()),
        startX, startY + (line++ * 20), scale, color);

    double mouseX, mouseY;
    glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &mouseX, &mouseY);
    arialFont->RenderText("Mouse Pos: (" + std::to_string((int)mouseX) + ", " + std::to_string((int)mouseY) + ")",
        startX, startY + (line++ * 20), scale, color);

    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    bool leftPressed = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool middlePressed = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

    arialFont->RenderText("Left Button: " + std::string(leftPressed ? "Down" : "Up"),
        startX, startY + (line++ * 20), scale, color);
    arialFont->RenderText("Middle Button: " + std::string(middlePressed ? "Down" : "Up"),
        startX, startY + (line++ * 20), scale, color);
}

