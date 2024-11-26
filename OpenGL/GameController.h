#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

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

    std::vector<Mesh*> meshBoxes;
    std::vector<Mesh*> lights;
    Mesh* meshLight = {};


    //vector<Camera> cameras;        // Array of Camera objects
    //vector<Resolution> resolutions; // Array of Resolution objects
    //int currentCameraIndex = 0;          // Current Camera index
    //int currentResolutionIndex = 0;      // Current Resolution index
};

#endif // GAME_CONTROLLER_H
