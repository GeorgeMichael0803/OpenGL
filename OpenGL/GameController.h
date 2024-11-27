#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "WindowController.h"

class GameController : public Singleton<GameController>
{
public:
    // Constructors / Destructors
    GameController() = default;
    virtual ~GameController() = default;

    // Methods
    void Initialize();
    void RunGame();
    std::vector<Mesh*>& GetLights() { return lights; }
    const Camera& GetCamera() { return camera; }

private:
    Camera camera={};

    Shader shaderColor = {};
    Shader shaderDiffuse = {};
    Shader shaderFont = {};
    Shader shaderColorByPosition = {}; // New shader for "Color By Position"

    std::vector<Mesh*> meshBoxes;
    std::vector<Mesh*> lights;
    Mesh* meshLight = {};



    // New variables for "Move Cubes to Sphere"
    Mesh* sphere;                 // Sphere model
    std::vector<Mesh*> cubes;     // Cube objects
    Mesh* suzanne = {}; // Suzanne model used in multiple modes



    
    // New private methods
    void HandleMoveCubesToSphere(GLFWwindow* win); // Logic for the "Move Cubes to Sphere" radio button
    void HandleColorByPosition(GLFWwindow* win, const Resolution& currentResolution);
    void SpawnCube();                              // Spawn a cube around the sphere
    void PrintCubeCount();                         // Print the number of cubes in the scene
    void Cleanup();
    void HandleMoveLight();


    //vector<Camera> cameras;        // Array of Camera objects
    //vector<Resolution> resolutions; // Array of Resolution objects
    //int currentCameraIndex = 0;          // Current Camera index
    //int currentResolutionIndex = 0;      // Current Resolution index
};

#endif // GAME_CONTROLLER_H
