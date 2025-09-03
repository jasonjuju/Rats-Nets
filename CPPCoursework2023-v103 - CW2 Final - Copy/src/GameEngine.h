#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H


#include "header.h"

#include "BaseEngine.h"

#include "BackgroundTileObject.h"

#include "PlayerObject.h"

#include "BaseEnemy.h"

#include "BaseStateManager.h"

#include "RatWarrior.h"

#include "Fireball.h"

#include "GameManager.h"

#include "Overlay.h"


class GameEngine :
    public BaseEngine
{
public:

    ~GameEngine() {
       delete currState;
       delete gameManager;
    }

    int virtInitialise() override;

    void virtSetupBackgroundBuffer();

    void virtKeyDown(int iKeyCode);

    int virtInitialiseObjects();

    void gameStartup();

    void resetGame();

    void changeState(int);

    void changeStateGiveValue(int, int);

    PlayerObject* getPlayer() { return player; };

    BackgroundTileObject* getBackground() { return runningBackground; }

    GameManager* getGameManager();


    Overlay* getOverlay() { return overlay; }




private:
    
    BackgroundTileObject* runningBackground = nullptr;
    PlayerObject* player = nullptr;

    BaseStateManager* currState = new StartState(this);

    GameManager* gameManager = nullptr;

    Overlay* overlay = nullptr;

};

#endif