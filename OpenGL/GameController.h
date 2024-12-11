#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "WindowController.h"
#include "Font.h"

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



    
    Mesh* sphere;                
    std::vector<Mesh*> cubes;     
    Mesh* suzanne = {}; 
    Mesh* lightSphere ;

    Font* arialFont;

    
    // New private methods
    void HandleMoveCubesToSphere(GLFWwindow* win); 
    void HandleColorByPosition(GLFWwindow* win, const Resolution& currentResolution);
    void SpawnCube();                              
    void Cleanup();
    void HandleMoveLight();
    void ResetPositions();
    void RenderCubeCount();

    //vector<Camera> cameras;        // Array of Camera objects
    //vector<Resolution> resolutions; // Array of Resolution objects
    //int currentCameraIndex = 0;          // Current Camera index
    //int currentResolutionIndex = 0;      // Current Resolution index
};

#endif // GAME_CONTROLLER_H
