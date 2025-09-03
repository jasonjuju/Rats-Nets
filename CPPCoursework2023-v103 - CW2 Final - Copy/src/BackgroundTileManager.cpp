#include "BackgroundTileManager.h"

void BackgroundTileManager::virtDrawTileAt(
    BaseEngine* pEngine, 
    DrawingSurface* pSurface, 
    int iMapX, int iMapY, 
    int iStartPositionScreenX, int iStartPositionScreenY
) const
{
    int iMapValue = getMapValue(iMapX, iMapY);

    switch (iMapValue) {
    case -1:
        return;
    default:
        break;
    }
    
    //Spritesheet has a width of 15
    //This gives up the x and y coords of the sprite with this value
    int mapX = iMapValue % 16;
    int mapY = iMapValue / 16;

    tileMap.renderImageWithMask(pSurface,
        64 * mapX,
        64 * mapY,
        iStartPositionScreenX,
        iStartPositionScreenY,
        64,
        64,
        0x000000
    );
}
