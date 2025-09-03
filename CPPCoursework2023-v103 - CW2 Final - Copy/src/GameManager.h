#pragma once
#include "DisplayableObjectContainer.h"
#include "BaseEntity.h"
#include "BaseEnemy.h"
#include "BaseRangedAttack.h"
#include "RatMage.h"



class GameEngine;

class GameManager :
    public DisplayableObjectContainer
{
//Contains all Enemies
//Can be used to spawn more enemies/kill enemies
public:
    GameManager(GameEngine*);


    //Do not destroy objects on exit. These will be destroyed by the engine
    ~GameManager() override {
        destroyOldObjects(false);
    }

    void addEntity(BaseEntity*);

    void removeEntity(BaseEntity*);

    void removeAllEntities();

    bool checkValidPosition(int xPos, int yPos);

    void summon(int);

    void summonWave(int time);

    void checkWave(int time);

    void updateWaveStrength();

    void checkAllCollisions(BaseRangedAttack*,int,int);

    void addPoints(int);

    int getScore() { return points; }

    void endGame();

    void saveGameAndExit();

    void loadGame();
    
    void startGame();


    

private: 
    GameEngine* engine;

    PlayerObject* player;

    BackgroundTileObject* background;

    int points = 0;

    

    //Determines the number/type of enemies that will spawn
    int waveStrength = 0;

    //Number of enemies that will spawn in a wave
    int spawnNumber = 1;

    //Limits the number of enemies in the game at once
    int maxSpawns = 5;

    //Chance of spawn being a mage, rather than a warrior
    double mageChance = 0.0;



};

