#pragma once
#include "DisplayableObject.h"
#include "TimerObject.h"
#include "SimpleImage.h"

class GameEngine;

class Overlay :
    public DisplayableObject
{
public:
    Overlay(GameEngine* pEngine);

    void virtDraw() override;

    void virtDoUpdate(int) override;

    long virtNotify(int iSignalNumber, int x, int y) override;

    void drawHealth();

    void drawScore();

    void drawTime();

    void drawBorder();

    std::time_t getCurrentTime() { return currTime; }

private:
    GameEngine* engine;

    std::time_t startTime;
    std::time_t currTime;

    int timeSinceStart = -1;

    Font* titleFont;

    //these could also all just be functions

    //Health display
    SimpleImage fullHeart;
    SimpleImage emptyHeart;

    //Score display
    Font* scoreFont;

    //Cooldown display?


};

