#pragma once
#include "BaseDisplay.h"
#include "header.h"
#include "SimpleButtons.h"
class PauseDisplay :
    public BaseDisplay
{
public:
    PauseDisplay(GameEngine*);


    void virtDraw() override;

    void virtDoUpdate(int iCurrentTime) override;


private:
    Font* titleFont;
    
    //Resume
    SwitchButton* resumeButton;

    //save and exit
    SwitchButton* saveAndExitButton;

    //exit
    ExitButton* exitButton;
};

