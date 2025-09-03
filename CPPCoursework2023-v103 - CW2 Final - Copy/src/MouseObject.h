#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "Psyjs31Engine.h"
class MouseObject :
    public DisplayableObject
{
public:
    MouseObject(BaseEngine*);

    void virtDraw();
    void virtDoUpdate(int iCurrentTime);

    Psyjs31Engine* getEngine() const {
        //casting BaseEngine* to Psyjs31Engine*
        return static_cast<Psyjs31Engine*>(m_pEngine);
    }

private:
    int mousePosX;
    int mousePosY;
    int objectPosX;
    int objectPosY;
    SimpleImage mouseImage;
};

