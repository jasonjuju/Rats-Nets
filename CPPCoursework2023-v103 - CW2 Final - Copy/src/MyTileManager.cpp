#include "MyTileManager.h"


void MyTileManager::virtDrawTileAt(
	BaseEngine* pEngine, 
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);
	unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12)
			+ (unsigned int)((iMapValue & 0xf0) << 8)
			+ (unsigned int)((iMapValue & 0xf) << 4);
	pSurface->drawOval (
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + getTileWidth() - 1,
		iStartPositionScreenY + getTileHeight() - 1,
		iColour); 
}