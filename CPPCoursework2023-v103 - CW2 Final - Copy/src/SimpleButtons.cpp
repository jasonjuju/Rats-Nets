#include "SimpleButtons.h"
#include "GameEngine.h"

ExitButton::ExitButton(GameEngine* pEngine, int x, int y, int width, int height) :
	BaseButton(pEngine,x,y,width,height,"EXIT")
{

}

void ExitButton::onClick()
{
	engine->setExitWithCode(0);
}



BackButton::BackButton(GameEngine* pEngine, int x, int y, int width, int height, int currState, int nextState) :
	BaseButton(pEngine, x, y, width, height, "BACK"),
	newState(nextState)
{
	setSignal(currState);
}

void BackButton::onClick()
{
	engine->changeState(newState);
	return;
}

SwitchButton::SwitchButton(GameEngine* pEngine, int x, int y, int width, int height, const char* text) :
	BaseButton(pEngine, x, y, width, height, text)
{
}

void SwitchButton::onClick()
{
	clicked = true;
}

bool SwitchButton::isClicked()
{
	return clicked;
}
