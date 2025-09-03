#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "PlayerObject.h"
#include "Psyjs31TileManager.h"


class Psyjs31Engine :
    public BaseEngine
{
public:
    Psyjs31Engine() {
        player = NULL;
    };
    virtual void virtSetupBackgroundBuffer() override;
    int virtInitialiseObjects();

    //Returns the player's object, for getting position etc
    PlayerObject* getPlayerObject() {
        return player;
    }

    //Returns the tile manager, for checking whether on tile
    Psyjs31TileManager* getTileManager() {
        return &tileGrid;
    }

private:
    //Stores the player's character. Set to null to avoid issues when getting
    PlayerObject* player;

protected:
    Psyjs31TileManager tileGrid;
};

