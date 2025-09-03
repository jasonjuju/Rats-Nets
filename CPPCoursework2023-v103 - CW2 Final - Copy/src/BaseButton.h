#pragma once
#include "header.h"
#include "DisplayableObject.h"


class GameEngine;

class BaseButton :
    public DisplayableObject
{
    public:
        BaseButton(GameEngine*, int x, int y, int width, int height, const char* text);

        ~BaseButton();

        virtual void onClick() {}

        virtual void virtDraw() override;

        void setSignal(int);

        long virtNotify(int iSignalNumber, int x, int y) override;

        void virtDoUpdate(int) override;

        void virtMouseMoved(int, int) override;

        void virtMouseDown(int iButton, int x, int y) override;

        void virtMouseUp(int iButton, int x, int y) override;

        void setTextSize(int size) { textSize = size; }

        void setMarginX(double x) { marginX = x; }

        void setMarginY(double y) { marginY = y; }

protected:

    int signalNum = -1;
    int buttonTopLeftX;
    int buttonTopLeftY;
    int buttonWidth;
    int buttonHeight;
    const char* text = nullptr;

    int textSize = 60;

    double marginX = 0.2;
    double marginY = 0.1;
    GameEngine* engine;

    bool hovered = false;
    bool clickedDown = false;

private:
    int lastClickX = -1;
    int lastClickY = -1;
    

   
};

