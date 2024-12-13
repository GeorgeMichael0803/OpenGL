#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "SkyBox.h"
#include "Camera.h"
#include "PostProcessor.h"
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


    void Reset();
    /*glm::vec3 getRandomPosition(float scale);*/
    void SpaceScene();
    void HandleMoveLight(float specularStrength, glm::vec3 specularColor);
    void HandleTransform(bool _transform, bool _rotate, bool _scale);
    void HandleWaterScene(bool _wireframe, bool tint, float frequency, float amplitude);

    void RenderTextGroup(const std::string& title, Mesh* mesh, bool includeScale = true);
    void RenderSpaceSceneText();

    

private:
    Camera camera={};
    PostProcessor postProcessor = {};

    Shader shaderColor = {};
    Shader shaderDiffuse = {};
    Shader shaderFont = {};
    Shader shaderSkybox = {};
    Shader shaderPost = {};

    std::vector<Mesh*> meshes;
    std::vector<Mesh*> lights;
    Mesh* meshLight = {};
    Skybox* skybox = nullptr;
    Mesh* lightSphere;
    Mesh* fighter;
    Mesh* fish;
    Mesh* fish_water;
    Mesh* light;
    //Font* arialFont;

    Font* arialFont;

    GLuint vao;


    bool translateChecked;
    bool rotateChecked;
    bool scaleChecked;
    bool wireframeChecked;
    bool tintChecked;
};

#endif // GAME_CONTROLLER_H
