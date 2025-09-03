#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include <ctime>

class Font;
class GameEngine;

class TimerObject :
    public DisplayableObject
{
public:
    TimerObject(GameEngine* pEngine);
    
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

private:
    std::time_t startTime;
    std::time_t currTime;

    Font* font;

    GameEngine* engine;
};

