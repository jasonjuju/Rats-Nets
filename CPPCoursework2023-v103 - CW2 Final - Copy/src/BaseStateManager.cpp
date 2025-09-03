#include "BaseStateManager.h"
#include "GameEngine.h"

#include "EndDisplay.h"
#include "PauseDisplay.h"
#include "StartDisplay.h"

//**********SUPERCLASS**********

void BaseStateManager::displayObjects()
{

	engine->fillBackground(0x6e1522);


	cout << engine->notifyAllObjectsGetCountNonZero(stateSignal) << endl;

	if (!engine->notifyAllObjectsGetCountNonZero(stateSignal)) {

		virtInitialise();

	}
}


//**********START STATE**********

StartState::StartState(GameEngine* pEngine) : BaseStateManager(pEngine)
{
	stateSignal = 1;
}

void StartState::virtInitialise()
{
	//engine->appendObjectToArray(new StartMenu(engine));
	engine->appendObjectToArray(new StartDisplay(engine));
}

void StartState::handleEscape()
{
	engine->setExitWithCode(0);
}





//**********RUNNING STATE**********

RunningState::RunningState(GameEngine* pEngine) : BaseStateManager(pEngine)
{
	stateSignal = 2;
}

void RunningState::virtInitialise()
{
	engine->gameStartup();
}

void RunningState::handleEscape()
{
	//Change to the state previously on
	engine->changeStateGiveValue(3, stateSignal);
}

//**********Paused STATE**********

PausedState::PausedState(GameEngine* pEngine) : BaseStateManager(pEngine)
{
	stateSignal = 3;
}

void PausedState::virtInitialise()
{
	engine->appendObjectToArray(new PauseDisplay(engine));
}

void PausedState::handleEscape()
{
	//Change to the state previously on
	engine->changeStateGiveValue(2, stateSignal);
}

//**********END STATE**********

EndState::EndState(GameEngine* pEngine) : BaseStateManager(pEngine)
{
	stateSignal = 4;
}

EndState::~EndState()
{
	if (display != nullptr) {
		display->destroy();
	}
}

void EndState::virtInitialise()
{
	display = new EndDisplay(engine);
	engine->appendObjectToArray(display);
}

void EndState::notifyValue(int value)
{
	display->setScore(value);
}




//**********SCORE STATE**********

ScoreState::ScoreState(GameEngine* pEngine) : BaseStateManager(pEngine)
{
	stateSignal = 5;
}

ScoreState::~ScoreState()
{
	
	//Cannot directly delete (called in middle of a loop for mouseUp)
	//Instead, set to be deleted at start of doUpdate
	if (display != nullptr) {
		display->destroy();
	}
	
	

}

void ScoreState::virtInitialise()
{
	display = new ScoreDisplay(engine);
	engine->appendObjectToArray(display);
}

void ScoreState::notifyValue(int value)
{
	//setScore
}


//Currently unimplemented, would be used for zoom + sound options
//**********OPTIONS STATE**********

OptionsState::OptionsState(GameEngine* pEngine) : BaseStateManager(pEngine)
{
	stateSignal = 6;
}

void OptionsState::virtInitialise()
{
}

void OptionsState::handleEscape()
{
	engine->changeState(/*previousState*/1);
}



