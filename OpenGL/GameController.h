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

private:
    Camera camera={};

    Shader shaderColor = {};
    Shader shaderDiffuse = {};

    Mesh meshBox = {};
    Mesh meshLight = {};


    //vector<Camera> cameras;        // Array of Camera objects
    //vector<Resolution> resolutions; // Array of Resolution objects
    //int currentCameraIndex = 0;          // Current Camera index
    //int currentResolutionIndex = 0;      // Current Resolution index
};

#endif // GAME_CONTROLLER_H
