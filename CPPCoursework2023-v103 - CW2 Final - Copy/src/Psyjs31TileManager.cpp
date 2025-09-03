#include "Psyjs31TileManager.h"

void Psyjs31TileManager::virtDrawTileAt(
    BaseEngine* pEngine,
    DrawingSurface* pSurface,
    int iMapX, int iMapY,
    int iStartPositionScreenX,
    int iStartPositionScreenY) const
{


    //Draw a rectangle to represent the tile
    pSurface->drawRectangle(
        iStartPositionScreenX,
        iStartPositionScreenY,
        iStartPositionScreenX + getTileWidth(),
        iStartPositionScreenY + getTileHeight(),
        getMapValue(iMapX, iMapY)
    );
}