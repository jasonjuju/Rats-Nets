#pragma once
#include "BaseDisplay.h"
#include "SimpleButtons.h"
#include "SubmitButton.h"
#include "TextInputBox.h"

class GameEngine;
class Font;

class EndDisplay :
    public BaseDisplay
{
public:
    EndDisplay(GameEngine*);

    ~EndDisplay();

    void virtDraw() override;

    void virtDoUpdate(int) override;

    void setScore(int);

    long virtNotify(int iSignalNumber, int x, int y) override;

    void virtKeyDown(int iKeyCode) override;

    void submit();

    void destroy() { markForDeletion = true; }

private:
    Font* font;
    Font* titleFont;
    int score = 0;

    int scoreboardLength = 10;



    ExitButton* exitButton;
    SubmitButton* submitButton;

    TextInputBox* inputBox;

    bool markForDeletion = false;
};

