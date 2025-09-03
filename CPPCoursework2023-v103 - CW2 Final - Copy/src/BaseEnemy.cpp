#include "BaseEnemy.h"
#include "PlayerObject.h"
#include "ImageManager.h"
#include "UtilCollisionDetection.h"
#include "GameEngine.h"

BaseEnemy::BaseEnemy(GameEngine* pEngine) : BaseEntity(pEngine)
{
    sprite = ImageManager::loadImage("resources/Enemies/Ratfolk_Warrior.png", true);

    m_iDrawWidth = 64;
    m_iDrawHeight = 64;
    playerX = player->getPlayerX();
    playerY = player->getPlayerY();


    m_iCurrentScreenX = 20;
    m_iCurrentScreenY = 20;
}

void BaseEnemy::virtDraw()
{
    if (!isVisible()) {
        return;
    }
    
    map->setXShift(spriteMapX * m_iDrawWidth);
    map->setYShift(spriteMapY * m_iDrawHeight);

    
    sprite.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface(),
        m_iCurrentScreenX,
        m_iCurrentScreenY,
        m_iDrawWidth,
        m_iDrawHeight,
        map
    );

    //Bounding box
    /*
    getEngine()->getForegroundSurface()->drawRectangle(
        m_iCurrentScreenX + 16,
        m_iCurrentScreenY + 28,
        m_iCurrentScreenX + m_iDrawWidth -20,
        m_iCurrentScreenY + m_iDrawHeight -4,
        0xFF0000
    );
    */
    
}



void BaseEnemy::virtMove(int iCurrentTime)
{

    switch (currState) {
    case Idle:
        performIdle();
        break;

    case Moving:
        performMoving();
        break;

    case Attack:
        performAttack();
        break;
    case SpecialAttack:
        //Have animation for this, but not implementing yet
        performSpecialAttack();
        break;
    case Hurt:
        performHurt();
        //All enemies die when their health reaches 0
        if (health <= 0) {
            changeState(Dead);
        }
        break;
    case Dead:
        if (spriteMapX == 4) {
            givePoints();
            isDead = true;
            //Remove object from game manager, avoids checking if hit
            engine->getGameManager()->removeDisplayableObject(this);
        }
        break;
    }

    TrackCooldowns(iCurrentTime);






}

//Run directly at the player
bool BaseEnemy::ChasePlayer()
{

    

    if (CollisionDetection::checkCircles(getXCentre(), getYCentre() + 16, playerX, playerY, 25)) {
        return true;
    }


    float deltaX = (float)(playerX - getXCentre());
    float deltaY = (float)(playerY - getYCentre());

    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    //float angle = atan2(enemyY - playerY, enemyX - playerX);
    

    float moveAmountX = deltaX / distance;
    float moveAmountY = deltaY / distance;

    float speed = 2.0f;


    storeX += speed * moveAmountX;
    storeY += speed * moveAmountY;


    //Trying to make movement smoother, m_iCurrentScreen is an int so store movement until it's a notable amount
    if (m_iCurrentScreenX + (int)storeX != m_iCurrentScreenX) {
        
        //if moving left, face left
        if (storeX < 0) {
            map->setFlipped(true);
            facingLeft = true;
        }
        else {
            map->setFlipped(false);
            facingLeft = false;
        }
        
        //Enemy would go at double speed if matching X or Y axis, this handles that case
        if (storeX > 1) {
            m_iCurrentScreenX += (int)speed - 1;
        }
        else {
            m_iCurrentScreenX -= (int)speed - 1;
        }

        storeX = 0.0;
    }
    if (m_iCurrentScreenY + (int)storeY != m_iCurrentScreenY) {

        if (storeY > 1) {

            m_iCurrentScreenY += (int)speed - 1;
        }
        else {
            m_iCurrentScreenY -= (int)speed - 1;
        }

        
        storeY = 0.0;
    }


    return false;
}

void BaseEnemy::MeleeAttack()
{
    int hitCheckX;

    //Change hitbox based on direction
    if (facingLeft == true) {
        hitCheckX = getXCentre() - 16;
    }
    else {
        hitCheckX = getXCentre() + 16;
    }
    
    int hitCheckY = getYCentre();

    //std::cout << "Sword Pos: " << hitCheckX << " " << hitCheckY << "\n Player Pos: " << playerX << " " << playerY << "\n";

    if (CollisionDetection::checkCircles(
        hitCheckX,
        hitCheckY, 
        playerX, 
        playerY, 
        32)) {
        
        player->hitPlayer(1);
    }
}

void BaseEnemy::TrackCooldowns(int iCurrentTime)
{
    //Effects any action that occurs every tick (second)
    if (iCurrentTime % 1000 / 10 == 0) {

        if (idleTime > 0) {
            idleTime--;
        }

        if (attackCD > 0) {
            attackCD--;
        }

        if (deathTime > 0 && isDead == true) {
            deathTime--;
            if (deathTime <= 0) {
                markForDeletion = true;
            }
        }



        //std::cout << "Tick\n";
    }
}

//Check if attack is in it's bounding box
bool BaseEnemy::checkInBoundingBox(int x, int y)
{
    

    if ((this->getTopLeftX() - x) < 0 &&
        (this->getTopLeftX() - x) > -64 &&
        (this->getTopLeftY() - y) < 0 &&
        (this->getTopLeftY() - y) > -64)
    {
        return true;
    }
    return false;
}

void BaseEnemy::takeDamage(int damage)
{
    health -= damage;
    if (health <= 0) {
        changeState(Dead);
    }
    else {
        changeState(Hurt);
    }
}

bool BaseEnemy::checkImmune()
{
    if (currState == Hurt || currState == Dead) {
        return true;
    }
    return false;
}

void BaseEnemy::givePoints()
{
    //Only give points on moment of death
    if (!isDead) {
        engine->getGameManager()->addPoints(pointValue);
    }
    
}
