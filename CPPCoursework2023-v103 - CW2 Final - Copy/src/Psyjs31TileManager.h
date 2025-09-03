#pragma once
#include "header.h"
#include "TileManager.h"

class Psyjs31TileManager :
    public TileManager
{

   
public:
    //Tiles are currently 100x100 pixels, in a 3x3 grid
    Psyjs31TileManager() : TileManager(100, 100, 3, 3) {

    }
    void virtDrawTileAt(BaseEngine* pEngine, 
       DrawingSurface* pSurface, 
        int iMapX, 
        int iMapY, 
        int iStartPositionScreenX, 
        int iStartPositionScreenY
    ) const override;


};




