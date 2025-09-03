#pragma once
#include "header.h"
#include "BaseButton.h"

class ExitButton :
    public BaseButton
{
public:
    ExitButton(GameEngine*, int x, int y, int width, int height);

    void onClick() override;
};



class BackButton :
    public BaseButton
{
public:
    BackButton(GameEngine*, int x, int y, int width, int height, int currState, int nextState);

    void onClick() override;
private:
    int newState = 1;
};

class SwitchButton :
    public BaseButton
{
public:
    SwitchButton(GameEngine*, int x, int y, int width, int height, const char* text);

    void onClick() override;

    bool isClicked();

    void setClicked(bool val) { clicked = val; }

private:
    bool clicked = false;
};