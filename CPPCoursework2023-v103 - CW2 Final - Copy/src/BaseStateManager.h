#ifndef BASE_STATE_MANAGER_H
#define BASE_STATE_MANAGER_H



#include "header.h"
#include "EndDisplay.h"
#include "ScoreDisplay.h"



class GameEngine;

class BaseStateManager
{


public:

//GameEngine* gameEngine
	BaseStateManager(GameEngine* gameEngine) {
		engine = gameEngine;
	};

	//Virtual destructor so it can be overwritten (to delete pointer etc)
	virtual ~BaseStateManager() {}
	
	void virtual virtInitialise() {};

	//Notify all objects with a code showing what is the current state
	void displayObjects();

	void virtual notifyValue(int) {};

	void virtual handleEscape() {};

protected:
	GameEngine* engine;
	int stateSignal = -1;
	int prevState = 1;


};


//**********START STATE**********


class StartState : 
	public BaseStateManager
{
public:
	StartState(GameEngine*);

	void virtInitialise() override;

	void handleEscape() override;
};




//**********RUNNING STATE**********


class RunningState :
	public BaseStateManager
{
public:
	RunningState(GameEngine*);

	void virtInitialise() override;

	void virtual handleEscape() override;


};

//**********PAUSED STATE**********


class PausedState :
	public BaseStateManager
{
public:
	PausedState(GameEngine*);

	void virtInitialise() override;

	void virtual handleEscape() override;

};

//**********END STATE**********

class EndState :
	public BaseStateManager
{
public:
	EndState(GameEngine*);

	~EndState();

	void virtInitialise() override;

	void notifyValue(int) override;

private:
	EndDisplay* display = nullptr;

};
//**********SCORE STATE**********

class ScoreState :
	public BaseStateManager
{
public:
	ScoreState(GameEngine*);

	~ScoreState();

	void virtInitialise() override;

	void notifyValue(int) override;

private:
	ScoreDisplay* display = nullptr;


};

//**********OPTIONS STATE**********

class OptionsState :
	public BaseStateManager
{
public:
	OptionsState(GameEngine*);

	void virtInitialise() override;

	void virtual handleEscape() override;

};

#endif