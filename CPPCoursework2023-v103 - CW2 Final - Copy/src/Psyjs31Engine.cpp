#include "Psyjs31Engine.h"
#include "DisplayableObject.h"

#include "TimerObject.h"
#include "MouseObject.h"
#include "ChaseObject.h"






//overrides background buffer function in the base class
void Psyjs31Engine::virtSetupBackgroundBuffer()
{
	//Set the background colour to grey
	fillBackground(0x222222);

	//loads an image to draw on the background
	SimpleImage backgroundImage = ImageManager::loadImage("leniDoro.png", true);

	//Draw shape onto background (lock while drawing)
	lockBackgroundForDrawing();

	//render image onto background
	backgroundImage.renderImage(getBackgroundSurface(), 0, 0, 550, 20, backgroundImage.getWidth(), backgroundImage.getHeight());

	//Draw purple oval at coords (10,10) of size 110x110
	drawBackgroundOval(10, 10, 110, 110, 0x441177);

	//Draw the test 'Background Text' in black
	drawBackgroundString(130, 180, "Background Text", 0xFFFFFF, NULL);

	


	//set top left coords to (50,350)
	tileGrid.setTopLeftPositionOnScreen(50, 350);

	//for all tiles in 3x3 grid,
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 

			//Set colour of tile to red
			tileGrid.setMapValue(i, j, 0xFF0000);

	//Draw tiles in tileGrid onto the background
	tileGrid.drawAllTiles(this, getBackgroundSurface());

	//Unlock once finished
	unlockBackgroundForDrawing();
}



//Sets all the initial object into an array
int Psyjs31Engine::virtInitialiseObjects()
{
	//Note that objects are being changed
	drawableObjectsChanged();

	//Destroy any objects from before this func called
	destroyOldObjects(true);

	//Create an array of objects (length 1)
	createObjectArray(0);


	//****The following no longer works, as PlayerObject has been modified too much****
	//Store player as a variable (so it can be accessed by a getter)
	//player = new PlayerObject(this);

	//Store PlayerObject at position 0 in the array
	//storeObjectInArray(0, player);

	//further objects can be added using 'appendObjectToArray'

	//add 2 other character objects to the stage
	appendObjectToArray(new MouseObject(this));
	appendObjectToArray(new ChaseObject(this));

	//Adding the timer object (objects at the back of the array are drawn last (nearest front))
	//appendObjectToArray(new TimerObject(this));


	return 0;
}


