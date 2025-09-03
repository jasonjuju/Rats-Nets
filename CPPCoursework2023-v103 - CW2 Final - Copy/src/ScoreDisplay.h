#pragma once
#include "header.h"
#include "BaseDisplay.h"
#include "SimpleButtons.h"
#include "Scoreboard.h"

class ScoreDisplay :
    public BaseDisplay
{
public:
    ScoreDisplay(GameEngine*);

    ~ScoreDisplay();

    void virtDraw() override;

    void virtDoUpdate(int) override;

    BackButton* getButton() { return backButton; }

    void destroy() { markForDeletion = true; }

    
    

private:
    Font* TitleFont = nullptr;
    Scoreboard* scoreboard;

    BackButton* backButton;

    bool markForDeletion = false;
};

