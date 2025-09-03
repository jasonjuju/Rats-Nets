#pragma once
#include "header.h"
#include "DisplayableObject.h"

class GameEngine;
class Font;

class BaseDisplay :
    public DisplayableObject
{
public:
    BaseDisplay(GameEngine*);

    virtual void virtDraw() override;

    virtual void drawText(const char* text, int x, int y, Font* font, int colour = 0x000000);

    virtual void virtDoUpdate(int);

    long virtNotify(int iSignalNumber, int x, int y) override;

protected:
    GameEngine* engine;

    int signalNum = -1;

    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;
};

