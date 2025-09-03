#pragma once
#include "header.h"
#include "TileManager.h"



class BackgroundTileManager :
    public TileManager
{
    
public:
    BackgroundTileManager()
        : TileManager (64,64, 23, 15) {
        
    }

    //Draws a tile to a surface (in our case background)
    void virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const override;


private:
    SimpleImage tileMap = ImageManager::loadImage("resources/Dungeon_Tileset.png", true);

};

