#pragma once
#include "BaseButton.h"

class SubmitButton :
    public BaseButton
{
public:

    SubmitButton(GameEngine* pEngine, int x, int y, int width, int height, int score);



    void onClick() override;

    bool isSubmitted();

private:
    int score;

    bool submitted = false;

};