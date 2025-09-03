#pragma once
#include "BaseDisplay.h"
#include "SimpleButtons.h"
#include "Torch.h"
class StartDisplay :
    public BaseDisplay
{
public:
    StartDisplay(GameEngine*);

    void virtDraw() override;

    void virtDoUpdate(int iCurrentTime) override;

    

private:
    Font* titleFont;

    //Start
    SwitchButton* startButton;
    //Load Save
    SwitchButton* loadButton;
    //Show leaderboard
    SwitchButton* leaderButton;
    //Exit
    ExitButton* exitButton;

    Torch* leftTorch;
    Torch* rightTorch;

    

};

