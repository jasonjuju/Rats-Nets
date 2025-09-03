#include "MouseObject.h"
#include "Psyjs31TileManager.h"

MouseObject::MouseObject(BaseEngine* pEngine) : DisplayableObject(pEngine)
{
    
    //loads an image to draw on the background
    SimpleImage backgroundImage = ImageManager::loadImage("testMOBAPlayer.png", true);

    m_iCurrentScreenX = 400;
    m_iCurrentScreenY = 450;


    objectPosX = m_iCurrentScreenX +(backgroundImage.getWidth()/2);
    objectPosY = m_iCurrentScreenY +(backgroundImage.getHeight()/2);

    //Give a initial value for mousePos to avoid any undefined behaviour
    mousePosX = NULL;
    mousePosY = NULL;

}

void MouseObject::virtDraw()
{
    mouseImage = ImageManager::loadImage("testMOBAPlayer.png", true);

    //render image onto background, left corner at (350,20)
    mouseImage.renderImageWithMask(getEngine()->getForegroundSurface(),
        0,
        0,
        m_iCurrentScreenX,
        m_iCurrentScreenY,
        mouseImage.getWidth(),
        mouseImage.getHeight()
    );



}


void MouseObject::virtDoUpdate(int iCurrentTime)
{
    
    int lastClickX = getEngine()->getMouseXClickedUp();
    int lastClickY = getEngine()->getMouseYClickedUp();



    if ((mousePosX != lastClickX || mousePosY != lastClickY)) {
        mousePosX = lastClickX;
        mousePosY = lastClickY;
        printf("X:%i Y:%i clicked\n", mousePosX, mousePosY);
    }
    
    //move object to be closer to last mouse click
    //changes objectPos for checking, and m_iCurrentScreen for actually moving the object

    //Outer if is to stop object approaching (0,0) at the start (realistically no reason to need to go to (0,0) so no issue there)
    if (mousePosX != 0 || mousePosY != 0) {
        if (objectPosX < mousePosX) {
            m_iCurrentScreenX += 2;
            objectPosX += 2;
        }
        if (objectPosX > mousePosX) {
            m_iCurrentScreenX -= 2;
            objectPosX -= 2;
        }
        if (objectPosY < mousePosY) {
            m_iCurrentScreenY += 2;
            objectPosY += 2;
        }
        if (objectPosY > mousePosY) {
            m_iCurrentScreenY -= 2;
            objectPosY -= 2;
        }
    }

    
    

    Psyjs31TileManager* tileGrid = getEngine()->getTileManager();

    //if the current position of the object is on a tile, change it's colour
    if (tileGrid->isValidTilePosition(objectPosX, objectPosY)) {
        printf("On tile at X: %i, Y: %i\n", objectPosX, objectPosY);
        tileGrid->setAndRedrawMapValueAt(
            tileGrid->getMapXForScreenX(objectPosX),
            tileGrid->getMapYForScreenY(objectPosY),
            0x00FF00,
            getEngine(),
            getEngine()->getBackgroundSurface()

        );

        
    }


    getEngine()->redrawDisplay();
}
