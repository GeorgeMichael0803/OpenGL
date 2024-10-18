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
    Shader shader = {};
    Mesh mesh = {};
    Camera camera={};

    glm::vec3 position1;
    glm::vec3 position2;
    glm::vec3 position3;

};

#endif // GAME_CONTROLLER_H
