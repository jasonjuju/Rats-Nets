#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "ImageManager.h"

class GameEngine;

class Torch :
    public DisplayableObject
{
public:
    Torch(GameEngine*, int, int);

    virtual void virtDraw() override;

    virtual void virtDoUpdate(int);

    long virtNotify(int iSignalNumber, int x, int y) override;

private:
    int currTime = 0;
    int spriteY = 0;
    GameEngine* engine;

    SimpleImage sprite;
};

