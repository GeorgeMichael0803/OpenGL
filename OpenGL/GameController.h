#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "NPC.h"

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
    Mesh playerMesh = {};
    Camera camera = {};

    glm::vec3 playerPosition = glm::vec3(0.0f, 0.0f, 0.0f);  // Player starting position

    std::vector<NPC> npcs;  // vector for 10 NPCs
};

#endif // GAME_CONTROLLER_H
