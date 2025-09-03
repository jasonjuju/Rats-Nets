#include "BaseRangedAttack.h"
#include "PlayerObject.h"
#include "GameEngine.h"

BaseRangedAttack::BaseRangedAttack(GameEngine* pEngine, int x, int y) : BaseEntity(pEngine)
{
	targetX = x;
	targetY = y;

    calculateAngle();
    
    
    //go into cast state
    changeState(Cast);
}


void BaseRangedAttack::virtMove(int iCurrentTime)
{
    switch (currState) {
    case Cast:
        performCast();
        break;

    case Flying:
        performFlying();
        break;

    case Hit:
        performHit();
        break;
    }

    //TrackCooldowns(iCurrentTime);
}



void BaseRangedAttack::calculateAngle()
{
    //Sprite isn't central, adjusting to be central to sprite (CLEANUP: Make function in player for this)
    int playerX = player->getXCentre() - 35;
    int playerY = player->getYCentre() - 20;


    float deltaX = (float)(targetX - player->getXCentre());
    float deltaY = (float)(targetY - player->getYCentre());

    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    moveAmountX = deltaX / distance;
    moveAmountY = deltaY / distance;


    //CLEANUP: This currently needs to be negative for the map, find out why
    //Not major problem as not used elsewhere
    angle = -atan2(deltaY, deltaX);

    
    if (moveAmountX < 0.0) {
        player->setFacingLeft(true);
    } 
    else {
        player->setFacingLeft(false);
    }

    m_iCurrentScreenX = playerX + (int)(20 * BASE_SPEED * moveAmountX);
    m_iCurrentScreenY = playerY + (int)(20 * BASE_SPEED * moveAmountY);



}

void BaseRangedAttack::performFlying()
{
    fly();
    
    //if projectile hits enemy
    engine->getGameManager()->checkAllCollisions(this, getXCentre(), getYCentre());

    //GameManager->checkHit(damage,damageradius)

    if (sqrt(distanceTravelledX * distanceTravelledX + distanceTravelledY * distanceTravelledY) > travelDistance) {
        changeState(Hit);
    }

}


void BaseRangedAttack::virtDraw()
{
    if (!isVisible()) {
        return;
    }

    
    projectileMap->setShifts(spriteMapX * m_iDrawWidth,
                             spriteMapY * m_iDrawHeight);

    projectileMap->setCentres(spriteMapX * m_iDrawWidth,
                              spriteMapY * m_iDrawHeight);

    projectileMap->setRotation(angle);
    
    sprite.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface(),
        m_iCurrentScreenX,
        m_iCurrentScreenY,
        m_iDrawWidth,
        m_iDrawHeight,
        projectileMap
    );
    
    
}

void BaseRangedAttack::fly()
{

    storeX += shotSpeed * moveAmountX;
    storeY += shotSpeed * moveAmountY;

    distanceTravelledX += shotSpeed * moveAmountX;
    distanceTravelledY += shotSpeed * moveAmountY;


    //Trying to make movement smoother, m_iCurrentScreen is an int so store movement until it's a notable amount
    if (m_iCurrentScreenX + (int)storeX != m_iCurrentScreenX) {

        //Would go at double speed if matching X or Y axis, this handles that case
        if (storeX > 1) {
            m_iCurrentScreenX += (int)shotSpeed - 1;
        }
        else {
            m_iCurrentScreenX -= (int)shotSpeed - 1;
        }

        storeX = 0.0;
    }
    if (m_iCurrentScreenY + (int)storeY != m_iCurrentScreenY) {

        if (storeY > 1) {

            m_iCurrentScreenY += (int)shotSpeed - 1;
        }
        else {
            m_iCurrentScreenY -= (int)shotSpeed - 1;
        }


        storeY = 0.0;
    }
}




