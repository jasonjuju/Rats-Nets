#include "PauseDisplay.h"
#include "GameEngine.h"

PauseDisplay::PauseDisplay(GameEngine* pEngine) :
	BaseDisplay(pEngine)
{
	signalNum = 3;

	

	minX = 0;
	minY = 0;
	maxX = (int)(1300 * 0.9);
	maxY = 800;

	titleFont = engine->getFont("Resources/PixelMusketeer.ttf", 72);


	//RESUME
	resumeButton = new SwitchButton(engine,
		60,
		150,
		630,
		100,
		"RESUME"
	);

	resumeButton->setSignal(signalNum);

	engine->appendObjectToArray(resumeButton);
	

	//SAVE AND EXIT
	saveAndExitButton = new SwitchButton(engine,
		60,
		280,
		630,
		100,
		"SAVE AND EXIT"
	);

	saveAndExitButton->setSignal(signalNum);

	engine->appendObjectToArray(saveAndExitButton);

	//EXIT
	exitButton = new ExitButton(engine,
		60,
		410,
		630,
		100
	);

	exitButton->setSignal(signalNum);

	engine->appendObjectToArray(exitButton);
	
}

void PauseDisplay::virtDraw()
{
	if (!isVisible()) {
		return;
	}

	drawText("PAUSED", 80, 40, titleFont, 0xd9d9d9);
}

void PauseDisplay::virtDoUpdate(int iCurrentTime)
{
	//if save and exit is clicked, save game state, then exit
	if (saveAndExitButton->isClicked()) {
		engine->getGameManager()->saveGameAndExit();

		//turn button off after (in case it tries calling again)
		saveAndExitButton->setClicked(false);

		engine->setExitWithCode(0);
	}

	if (resumeButton->isClicked()) {
		engine->changeState(2);
		resumeButton->setClicked(false);
	}

}
