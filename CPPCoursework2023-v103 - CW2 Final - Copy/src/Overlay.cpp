#include "Overlay.h"
#include "GameEngine.h"
#include <iomanip>

Overlay::Overlay(GameEngine* pEngine) : DisplayableObject(pEngine)
{
	engine = pEngine;

	titleFont = engine->getFont("resources/PixelMusketeer.ttf", 36);
	scoreFont = engine->getFont("resources/PixelEmulator.ttf", 24);

	fullHeart = ImageManager::loadImage("resources/Player/Full_Heart.png", true);
	emptyHeart = ImageManager::loadImage("resources/Player/Empty_Heart.png", true);

	//Track the time the game started
	startTime = std::time(nullptr);

	currTime = 0;

}

void Overlay::virtDraw()
{
	if (!isVisible()) {
		return;
	}

	engine->getForegroundSurface()->drawRectangle(
		0, 5,
		engine->getWindowWidth(),
		95, 
		0x6e1522);

	engine->getForegroundSurface()->drawRectangle(
		0, 95,
		engine->getWindowWidth(),
		100,
		0x401010);

	
	//Draw information on overlay
	drawHealth();
	drawTime();
	drawScore();

	//draw border of screen
	drawBorder();
}

void Overlay::virtDoUpdate(int iCurrentTime)
{

	if (!isVisible()) {
		return;
	}

	if (timeSinceStart != (currTime - startTime)) {
		timeSinceStart = currTime - startTime;



		//**Disable this if you want no enemies to spawn**
		//summon new wave every 5 seconds
		if (timeSinceStart % 5 == 0) {
			engine->getGameManager()->summonWave(timeSinceStart);
		}

	}





	redrawDisplay();
}

long Overlay::virtNotify(int iSignalNumber, int x, int y)
{
	switch (iSignalNumber) {

	case 2:
		setVisible(true);
		return 1;
		break;
	default:
		setVisible(false);
		return 0;
	}
	return 0;
}

void Overlay::drawHealth()
{
	//Perhaps add background behind text?

	engine->getForegroundSurface()->drawFastString(
		39, 4,
		"HEALTH",
		0xd9d9d9,
		titleFont);

	SimpleImage currImage;

	for (int i = 0; i < 3; i++) {
		if (engine->getPlayer()->getHealth() > i) {

			currImage = fullHeart;
		}
		else {
			currImage = emptyHeart;
		}

		currImage.renderImageWithMask(engine->getForegroundSurface(),
			0, 0,
			33 + 42*i, 45,
			fullHeart.getWidth(),
			fullHeart.getHeight());
	}

	
}

void Overlay::drawScore()
{
	engine->getForegroundSurface()->drawFastString(
		engine->getWindowWidth() - 155, 9,
		"SCORE",
		0xd9d9d9,
		titleFont);

	//Using a stringstream to fill blank spaces with zeros (always 8 char width)
	stringstream displayScore;
	displayScore << setw(8) << setfill('0') << engine->getGameManager()->getScore();

	
	engine->getForegroundSurface()->drawFastString(
		engine->getWindowWidth() - 180, 50,
		displayScore.str().c_str(),
		0xd9d9d9,
		scoreFont);

}

void Overlay::drawTime()
{
	//initialise the current time
	currTime = std::time(nullptr);

	stringstream seconds;
	stringstream minutes;


	//Buffer to store currTime as char*
	char msg[128];

	

	minutes << setw(2) << setfill('0') << (currTime - startTime)/60;
	seconds << setw(2) << setfill('0') << (currTime - startTime)%60;


	//save current time to msg character buffer (type __int64)
	sprintf(msg, "%s:%s", minutes.str().c_str(), seconds.str().c_str());

	engine->getForegroundSurface()->drawFastString(
		620, 30,
		msg,
		0xd9d9d9,
		titleFont);


}

void Overlay::drawBorder()
{

	engine->getForegroundSurface()->drawRectangle(
		0, 0,
		engine->getWindowWidth(),
		5,
		0x401010);

	engine->getForegroundSurface()->drawRectangle(
		0, 0,
		5,
		engine->getWindowHeight(),
		0x401010);

	engine->getForegroundSurface()->drawRectangle(
		0,
		engine->getWindowHeight() - 5,
		engine->getWindowWidth(),
		engine->getWindowHeight(),
		0x401010);

	engine->getForegroundSurface()->drawRectangle(
		engine->getWindowWidth() - 5,
		0,
		engine->getWindowWidth(),
		engine->getWindowHeight(),
		0x401010);
}
