#include "BaseButton.h"
#include "GameEngine.h"

BaseButton::BaseButton(GameEngine* pEngine, int x, int y, int width, int height, const char* text) :
	DisplayableObject(pEngine),
	text(text)
{
	engine = pEngine;

	buttonTopLeftX = x;
	buttonTopLeftY = y;
	buttonWidth = width;
	buttonHeight = height;
}

BaseButton::~BaseButton()
{
	engine->drawableObjectsChanged();
	engine->removeDisplayableObject(this);
}


void BaseButton::virtDraw()
{
	if (!isVisible()) {
		return;
	}

	if (clickedDown && hovered) {
		engine->getForegroundSurface()->drawRectangle(
			buttonTopLeftX,
			buttonTopLeftY,
			buttonTopLeftX + buttonWidth,
			buttonTopLeftY + buttonHeight,
			0xcc8400
		);
	}
	else if (hovered) {
		engine->getForegroundSurface()->drawRectangle(
			buttonTopLeftX,
			buttonTopLeftY,
			buttonTopLeftX + buttonWidth,
			buttonTopLeftY + buttonHeight,
			0xe69500
		);
	}
	else {
		engine->getForegroundSurface()->drawRectangle(
			buttonTopLeftX,
			buttonTopLeftY,
			buttonTopLeftX + buttonWidth,
			buttonTopLeftY + buttonHeight,
			0xFFA500
		);
	}
	

	engine->getForegroundSurface()->drawFastString(
		buttonTopLeftX +(int)(marginX * buttonWidth),
		buttonTopLeftY +(int)(marginY * buttonHeight),
		text,
		0x000000,
		engine->getFont("resources/PixelMusketeer.ttf", textSize));
}

void BaseButton::setSignal(int sig)
{
	signalNum = sig;
}



void BaseButton::virtDoUpdate(int iCurrentTime) 
{
	if (!isVisible()) {
		return;
	}



	redrawDisplay();
}

void BaseButton::virtMouseMoved(int x, int y)
{
	if (
		x >= buttonTopLeftX && x <= buttonTopLeftX + buttonWidth &&
		y >= buttonTopLeftY && y <= buttonTopLeftY + buttonHeight
		) {
		hovered = true;
	}
	else {
		hovered = false;
	}

}

void BaseButton::virtMouseDown(int iButton, int x, int y)
{
	if (hovered && isVisible()) {
		clickedDown = true;
	}
	else {
		clickedDown = false;
	}
}

void BaseButton::virtMouseUp(int iButton, int x, int y)
{
	if (hovered && isVisible()) {
		onClick();
	}

	clickedDown = false;
}





long BaseButton::virtNotify(int iSignalNumber, int x, int y)
{
	if (iSignalNumber == signalNum) {
		setVisible(true);
		return 1;
	}

	setVisible(false);
	return 0;
}