#include "StartDisplay.h"
#include "GameEngine.h"

StartDisplay::StartDisplay(GameEngine* pEngine) :
	BaseDisplay(pEngine)
{
	signalNum = 1;

	titleFont = engine->getFont("Resources/PixelMusketeer.ttf", 72);

	minX = 0;
	minY = 0;
	maxX = 1300;
	maxY = 800;

	startButton = new SwitchButton(engine,
		330,
		200,
		670,
		100,
		"NEW GAME"
	);

	startButton->setSignal(1);

	engine->appendObjectToArray(startButton);

	loadButton = new SwitchButton(engine,
		330,
		350,
		670,
		100,
		"LOAD SAVE"
	);

	loadButton->setSignal(1);

	engine->appendObjectToArray(loadButton);
	

	leaderButton = new SwitchButton(engine,
		330,
		500,
		670,
		100,
		"LEADERBOARD"
	);

	leaderButton->setSignal(1);

	engine->appendObjectToArray(leaderButton);


	


	exitButton = new ExitButton(engine, 
		330,
		650,
		670,
		100
	);

	exitButton->setSignal(1);

	engine->appendObjectToArray(exitButton);


	leftTorch = new Torch(engine, 400, 75);
	rightTorch = new Torch(engine, 865, 75);

	engine->appendObjectToArray(leftTorch);
	engine->appendObjectToArray(rightTorch);

}

void StartDisplay::virtDraw()
{
	if (!isVisible()) {
		return;
	}

	drawText("RAT'S NEST", 480, 60, titleFont, 0xd9d9d9);
}

void StartDisplay::virtDoUpdate(int iCurrentTime)
{


	if (startButton->isClicked()) {
		engine->resetGame();
		engine->changeState(2);
		startButton->setClicked(false);
	}
	if (loadButton->isClicked()) {
		engine->resetGame();
		engine->changeState(2);
		if (engine->getBackground() == nullptr) {
			cout << "ENGINES A NULL POINTER\n";
		}
		engine->getGameManager()->loadGame();
		

		loadButton->setClicked(false);
	}
	if (leaderButton->isClicked()) {
		engine->changeState(5);

		leaderButton->setClicked(false);
	}
}
