#pragma once
#include "header.h"  
#include "BaseEngine.h"  
#include "MyObjectB.h" 
class MyObjectB :
    public DisplayableObject
{
public:
    MyObjectB(BaseEngine* pEngine)
        : DisplayableObject(pEngine) {
        m_iCurrentScreenX = 100;
        m_iCurrentScreenY = 200;
        m_iDrawWidth = 100;
        m_iDrawHeight = 200;     
    }

    void virtDraw();
    void virtDoUpdate(int iCurrentTime);
};



