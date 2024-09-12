#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Mesh.h"

class GameController : public Singleton<GameController>
{
public:
    // Constructors / Destructors
    GameController();
    virtual ~GameController() { }

    // Methods
    void Initialize();
    void RunGame();

private:
    Mesh mesh;
};

#endif // GAME_CONTROLLER_H

