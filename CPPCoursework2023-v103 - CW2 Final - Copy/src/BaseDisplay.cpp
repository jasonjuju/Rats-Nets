#include "BaseDisplay.h"
#include "GameEngine.h"

BaseDisplay::BaseDisplay(GameEngine* pEngine) :
	DisplayableObject(pEngine)
{
	engine = pEngine;
}

void BaseDisplay::virtDraw()
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
		0x004400);
}

void BaseDisplay::drawText(const char* text, int x, int y, Font* font, int colour)
{
	engine->getBackgroundSurface()->drawFastString(
		minX + x,
		minY + y,
		text,
		colour,
		font);
}

void BaseDisplay::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible()) {
		return;
	}

	redrawDisplay();
}

long BaseDisplay::virtNotify(int iSignalNumber, int x, int y)
{
	if (iSignalNumber == signalNum) {
		setVisible(true);
		return 1;
	}
	setVisible(false);
	return 0;
}
