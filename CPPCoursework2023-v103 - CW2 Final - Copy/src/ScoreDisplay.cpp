#include "ScoreDisplay.h"
#include "GameEngine.h"

ScoreDisplay::ScoreDisplay(GameEngine* pEngine) :
	BaseDisplay(pEngine)
{
	signalNum = 5;

	minX = (int)(1300 * 0.1);
	minY = (int)(800 * 0.1);
	maxX = (int)(1300 * 0.9);
	maxY = 800;

	TitleFont = engine->getFont("resources/pixelMusketeer.ttf", 60);


	scoreboard = new Scoreboard(engine, 
		maxX - 20,
		maxY - 200,
		minX + 20,
		minY + 100
	);

	backButton = new BackButton(engine,
		200,
		620,
		220,
		100,
		5,
		1
	);

	engine->appendObjectToArray(backButton);

}

ScoreDisplay::~ScoreDisplay()
{
	
	delete scoreboard;
	
}



void ScoreDisplay::virtDraw()
{
	if (!isVisible()) {
		return;
	}


	//Temp background until I get a decent image
	engine->getBackgroundSurface()->drawRectangle(
		minX,
		minY,
		maxX,
		maxY,
		0x003300);
	
	drawText("SCOREBOARD",
		340,
		20,
		TitleFont,
		0x000000);

	scoreboard->drawBoard();
}



void ScoreDisplay::virtDoUpdate(int)
{

	//Delete when ready to be deleted
	if (markForDeletion) {
		engine->removeDisplayableObject(this);
		delete backButton;
		delete this;
		return;
	}


	if (!isVisible()) {
		return;
	}

	redrawDisplay();
}




