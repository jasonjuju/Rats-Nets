#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "Psyjs31Engine.h"
class ChaseObject :
    public DisplayableObject
    
{
public:
    ChaseObject(BaseEngine* pEngine);
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    //return as a Psyjs31Engine instead of a BaseEngine, allowing us to use added functions defined in Psyjs31Engine
    Psyjs31Engine* getEngine() const {
        //casting BaseEngine* to Psyjs31Engine*
        return static_cast<Psyjs31Engine*>(m_pEngine);
    }

private:
    //Stores the image file
    SimpleImage chaseImage;

    //Stores the name of the image file
    std::string image;
};
