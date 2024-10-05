#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include <glm/glm.hpp>  // For glm::distance
#include <glm/gtc/constants.hpp>  // For pi

void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow(); // GLFW native window, use nullptr for native
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f); // Dark blue background
    glEnable(GL_CULL_FACE);

    shader = Shader();
    shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    camera = Camera(WindowController::GetInstance().GetResolution());
    camera.LookAt({ 0, 0, 50 }, { 0, 0, 0 }, { 0, 1, 0 });

    playerMesh = Mesh();
    playerMesh.Create(&shader);

    // Initialize NPCs
    for (int i = 0; i < 10; ++i) {
        NPC npc;
        npc.Create(&shader);
        npcs.push_back(npc);
    }
}

void GameController::RunGame() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow();

    do {
        System::Windows::Forms::Application::DoEvents(); 

        // Player movement logic
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) playerPosition.y += 0.035f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) playerPosition.y -= 0.035f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) playerPosition.x -= 0.035f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) playerPosition.x += 0.035f;

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT );  //| GL_DEPTH_BUFFER_BIT

        // Rendering the player
        glm::mat4 playerWorldMatrix = glm::translate(glm::mat4(1.0f), playerPosition);
        playerMesh.Render(camera.GetProjection() * camera.GetView() * playerWorldMatrix);

        // NPC logic
        for (int i = 0; i < 10; ++i) {
            glm::vec3 npcPosition = npcs[i].GetPosition();
            float distance = glm::distance(playerPosition, npcPosition);

            // NPC moves away if closer than 10 units
            if (distance < 10.0f) {
                glm::vec3 direction = glm::normalize(npcPosition - playerPosition);  // Direction away from player
                npcPosition += direction * 0.01f;
            }
            // NPC moves closer if farther than 11 units
            else if (distance > 11.0f) {
                glm::vec3 direction = glm::normalize(playerPosition - npcPosition);  // Direction towards player
                npcPosition += direction * 0.01f;
            }

            // NPC tagged if within 1 unit
            if (distance < 1.0f) {
                npcs[i].SetTagged(true);
            }

            // Update NPC's position
            npcs[i].SetPosition(npcPosition);

            //To Render NPC facing the player
            npcs[i].Render(camera.GetProjection() * camera.GetView(), playerPosition);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    // Cleanup
    playerMesh.Cleanup();
    for (int i = 0; i < 10; ++i) npcs[i].Cleanup();
    shader.Cleanup();
}
