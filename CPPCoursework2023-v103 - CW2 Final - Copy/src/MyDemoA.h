#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "MyTileManager.h"
class MyDemoA :
    public BaseEngine
{
public:
    void virtSetupBackgroundBuffer();
    void virtMouseDown(int, int, int);
    void virtKeyDown(int);
    int virtInitialiseObjects();


protected:
    MyTileManager tm; 

    
};