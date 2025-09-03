#include "ChaseObject.h"
#include "UtilCollisionDetection.h"


ChaseObject::ChaseObject(BaseEngine* pEngine) : DisplayableObject(pEngine)
{
    SimpleImage chaseImage = ImageManager::loadImage("testEnemy.png", true);

    m_iCurrentScreenX = 400;
    m_iCurrentScreenY = 300;
    m_iDrawWidth = chaseImage.getWidth();
    m_iDrawHeight = chaseImage.getHeight();

    image = "testEnemy.png";

}

void ChaseObject::virtDraw()
{

    //loads an image to draw on the background
    chaseImage = ImageManager::loadImage(image, true);

    //render image onto background, left corner at (350,20)
    chaseImage.renderImageWithMask(getEngine()->getForegroundSurface(),
        0,
        0,
        m_iCurrentScreenX,
        m_iCurrentScreenY,
        chaseImage.getWidth(),
        chaseImage.getHeight()
    );
    

}

void ChaseObject::virtDoUpdate(int iCurrentTime)
{
    //This object should follow the player, and try to get it's coords to match the player's coords
    //first get player's position
    //then compare them (same code as mouseobject roughly)

    PlayerObject* player = getEngine()->getPlayerObject();
    

    int centreX = player->getXCentre();
    int centreY = player->getYCentre();

    int playerWidth = player->getDrawWidth();
    int playerHeight = player->getDrawHeight();


    //get all of the player object's location info
    int playerCoordXL = centreX - playerWidth/2;
    int playerCoordXR = centreX + playerWidth/2;
    int playerCoordYT = centreY - playerHeight/2;
    int playerCoordYB = centreY + playerHeight/2;

    int playerCoordXC = centreX;
    int playerCoordYC = centreY;

    
    chaseImage = ImageManager::loadImage(image, true);

    //if there is a collision between the player and the chasing enemy, change enemy's colour
    if (CollisionDetection::checkRectangles(
        m_iCurrentScreenX,
        m_iCurrentScreenX + chaseImage.getWidth(),
        m_iCurrentScreenY,
        m_iCurrentScreenY + chaseImage.getHeight(),
        playerCoordXL,
        playerCoordXR,
        playerCoordYT,
        playerCoordYB
    )) {
        //change sprite
        image = "testEnemy2.png";
    }
    //else revert to old sprite and move towards player
    else {
        image = "testEnemy.png";

        //change x and y to be closer to the player's position
        if (this->getXCentre() < centreX) {
            m_iCurrentScreenX += 2;
        }
        if (this->getXCentre() > centreX) {
            m_iCurrentScreenX -= 2;
        }
        if (this->getYCentre() < centreY) {
            m_iCurrentScreenY += 2;
        }
        if (this->getYCentre() > centreY) {
            m_iCurrentScreenY -= 2;
        }
    }

   
    getEngine()->redrawDisplay();
}


