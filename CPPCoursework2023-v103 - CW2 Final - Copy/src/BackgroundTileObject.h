#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "BackgroundTileManager.h"
#include "DrawingSurface.h"
#include "BaseEntity.h"
#include "PlayerObject.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class GameEngine;

class BackgroundTileObject :
    public BaseEntity
{
public: 
    BackgroundTileObject(GameEngine*);

    ~BackgroundTileObject() {
        delete pixelBuffer;
    }

    void setBackground(int mapCode);

    void virtDoUpdate(int iCurrentTime) override;
    void virtDraw() override;

    void CheckInput();

    bool coordOutBounds(int x, int y) const {
        return (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight);
    }

    //Need seperate checks for play area
    bool checkHitBoxBounds(int, int, int, int);

    //Checks whether a specified coordinate collides with a wall
    bool checkCollision(int, int);

    //Takes in an int representing direction and checks whether a move would result in a collision
    bool checkMove(int);

    int getPlayerAgainstWall() {
            return playerAgainstWall;
    }

    void MoveTileGrid();
    long virtNotify(int iSignalNumber, int x, int y) override;

    int getXCoord() { return xCoord; }
    int getYCoord() { return yCoord; }

    int getXOffset() { return m_iCurrentScreenX; }
    int getYOffset() { return m_iCurrentScreenY; }

    void setXCoord(int val) { xCoord = val; }
    void setYCoord(int val) { yCoord = val; }

    void setXOffset(int val) { m_iCurrentScreenX = val; }
    void setYOffset(int val) { m_iCurrentScreenY = val; }

    void redrawTiles();

    int getMap() { return map; }

private:
    int const TILE_GRID_WIDTH;
    int const TILE_GRID_HEIGHT;
    int xCoord;
    int yCoord;
    int mapWidth;
    int mapHeight;

    int map;

    int playerTileMinX = 0;
    int playerTileMaxX = 0;
    int playerTileMinY = 0;
    int playerTileMaxY = 0;

    int playerAgainstWall = -1;

    DrawingSurface* pixelBuffer;

    vector<vector<int>> mapCodes;
    vector<vector<int>> mapWallCodes;
    PlayerObject* player = nullptr;

    BackgroundTileManager tileGrid;
    BackgroundTileManager tileWallGrid;
    
};

