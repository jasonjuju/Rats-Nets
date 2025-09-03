#include "TimerObject.h"
#include "GameEngine.h"

//Object to count time since program started


TimerObject::TimerObject(GameEngine* pEngine) : DisplayableObject(pEngine)
{
	engine = pEngine;

	//Track the time the game started
	startTime = std::time(nullptr);
	
	//initialise the current time
	currTime = std::time(nullptr);

	

	
}

void TimerObject::virtDraw()
{
	char msg[128];

	

	//save current time to msg character buffer (type __int64)
	sprintf(msg, "Current Time: %I64u", (currTime-startTime));

	//Draw 'msg' in black 
	getEngine()->drawForegroundString(560, 30, msg, 0x000000, NULL);
	
}


void TimerObject::virtDoUpdate(int iCurrentTime)
{
	//get current time
	currTime = std::time(nullptr);

	redrawDisplay();
}
