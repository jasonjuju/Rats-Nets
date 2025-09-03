#include "GameEngine.h"



int GameEngine::virtInitialise()
{
	getFont("resources/PixelMusketeer.ttf", 36);

	lockBackgroundForDrawing();
	virtSetupBackgroundBuffer();
	unlockBackgroundForDrawing();

	// Create the moving objects
	virtInitialiseObjects();

	//Tell objects mouse position and state
	notifyObjectsAboutMouse(true);

	//notifyObjectsAboutKeys(true);
	

	//Maybe try move most of this into states?
	//Here currently for loading game
	
	changeState(1);

	getForegroundSurface()->setTransparentColour(0xFF00FF);

	return 0;
}

void GameEngine::virtSetupBackgroundBuffer()
{
	//Set the background colour to green 
	fillBackground(0x00FF00);

	//Start game on the startup screen
	//currState = Start;

}

void GameEngine::virtKeyDown(int iKeyCode)
{

	switch (iKeyCode) {

	/* 
	*Testing keys 
	*changes states without having to play through game each time
	//Start state
	case SDLK_1:
		printf("Start state\n");
		changeState(1);
		break;

	//Running state
	case SDLK_2:
		printf("Running state\n");
		changeState(2);
		break;

		//Running state
	case SDLK_3:
		printf("Win state\n");
		changeState(3);
		break;

		//Running state
	case SDLK_4:
		printf("Loss state\n");
		changeState(4);
		break;

		//Running state
	case SDLK_5:
		printf("Options state\n");
		changeState(5);
		break;

	summon a single Rat Warrior
	case SDLK_o:
		gameManager->summon(1);
		break;
	*/

	case SDLK_ESCAPE:
		currState->handleEscape();
		break;
	

	default:
		return;

	}

	

	redrawDisplay();

}


int GameEngine::virtInitialiseObjects()
{


	//Note that objects are being changed
	drawableObjectsChanged();

	//Destroy any objects from before this func called
	destroyOldObjects(true);

	//Create an array of objects (length 1)
	createObjectArray(0);
	
	setAllObjectsVisible(false);
	
	currState->displayObjects();

	


	// TODO: Add your implementation code here.
	return 0;
}

//Initialise all objects related to the running of the game
void GameEngine::gameStartup()
{

	player = new PlayerObject(this);

	runningBackground = new BackgroundTileObject(this);

	appendObjectToArray(runningBackground);

	gameManager = new GameManager(this);

	appendObjectToArray(player);

	overlay = new Overlay(this);

	appendObjectToArray(overlay);
	
}

void GameEngine::resetGame()
{
	//remove objects from engine, then replace them with a nullptr
	if (player != nullptr) {
		removeDisplayableObject(player);
		delete player;
		player = nullptr;
	}
	if (runningBackground != nullptr) {
		removeDisplayableObject(runningBackground);
		delete runningBackground;
		runningBackground = nullptr;
	}
	if (overlay != nullptr) {
		removeDisplayableObject(overlay);
		delete overlay;
		overlay = nullptr;
	}

	//with gameManager, delete all old objects as well
	if (gameManager != nullptr) {
		gameManager->removeAllEntities();
		gameManager->destroyOldObjects(true);
		delete gameManager;
		gameManager = nullptr;
	}
	
	cout << notifyAllObjectsGetCountNonZero(2) << "TEST" << endl;

}


//Delete the current state, and replace it with a new state based on the given GameState
void GameEngine::changeState(int newState)
{
	delete currState;
	

	switch (newState) {
	case 1:
		currState = new StartState(this);
		break;
	case 2:
		currState = new RunningState(this);
		break;
	case 3:
		currState = new PausedState(this);
		break;
	case 4:
		currState = new EndState(this);
		break;
	case 5:
		currState = new ScoreState(this);
		break;
	case 6:
		currState = new OptionsState(this);
		break;
	default:
		currState = nullptr;
		cout << "current state not assigned, this should not happen";
	}


	currState->displayObjects();
	
	
	
}

//Change states, while also giving the new state a value (score or prev state)
void GameEngine::changeStateGiveValue(int newState, int value)
{
	changeState(newState);
	currState->notifyValue(value);
}

GameManager* GameEngine::getGameManager()
{
	return gameManager; 
}



