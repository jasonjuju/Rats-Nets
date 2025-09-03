#include "ImageManager.h" 
#include "MyObjectB.h"

#include "MyDemoA.h"


void MyDemoA::virtSetupBackgroundBuffer()
{	
	fillBackground(0x111111);
	SimpleImage image = ImageManager::loadImage("demo.png", true);
	image.renderImage(getBackgroundSurface(), 0, 0, 10, 10, image.getWidth(), image.getHeight());

	for (int i = 0; i < 15; i++)  
		for (int j = 0; j < 15; j++)  
			tm.setMapValue(i, j, rand());
			tm.setTopLeftPositionOnScreen(50, 50);
			tm.drawAllTiles(this, getBackgroundSurface());
}


void MyDemoA::virtMouseDown(int iButton, int iX, int iY)
{
	// TODO: Add your implementation code here.
	printf("Mouse clicked at %d %d\n", iX, iY);   
	if (iButton == SDL_BUTTON_LEFT) {
		if (tm.isValidTilePosition(iX, iY)) 
			{  
			int mapX = tm.getMapXForScreenX(iX);
			int mapY = tm.getMapYForScreenY(iY);
			int value = tm.getMapValue(mapX, mapY);
			tm.setAndRedrawMapValueAt(mapX, mapY, value+rand(), this, getBackgroundSurface() );
			redrawDisplay(); // Force background to be redrawn to foreground 
		} 
	} 
	else if (iButton == SDL_BUTTON_RIGHT) {
		lockBackgroundForDrawing();
		drawBackgroundOval(iX - 10, iY - 10, iX + 10, iY + 10, 0x0000ff);
		unlockBackgroundForDrawing();
		redrawDisplay(); // Force background to be redrawn to foreground  
	} 
}


void MyDemoA::virtKeyDown(int iKeyCode)
{

	switch (iKeyCode) { 
	case ' ':   
		lockBackgroundForDrawing();
		virtSetupBackgroundBuffer();
		unlockBackgroundForDrawing();
		redrawDisplay();
		break;
	}

}


int MyDemoA::virtInitialiseObjects()
{

	drawableObjectsChanged();   // Destroy any existing objects  
	destroyOldObjects(true);   // Creates an array big enough for the number of objects that you want.  
	createObjectArray(1);   // You MUST set the array entry after the last one that you create to NULL,  
	// so that the system knows when to stop.  
	storeObjectInArray(0, new MyObjectB(this));   
	setAllObjectsVisible(true);
	return 0;
}
