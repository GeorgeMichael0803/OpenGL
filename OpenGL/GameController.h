#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "SkyBox.h"
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
    Shader shaderSkybox = {};

    std::vector<Mesh*> meshes;
    std::vector<Mesh*> lights;
    Mesh* meshLight = {};
    Skybox* skybox = nullptr;

};

#endif // GAME_CONTROLLER_H
