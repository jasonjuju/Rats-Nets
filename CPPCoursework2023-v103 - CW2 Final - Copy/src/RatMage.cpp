#include "RatMage.h"

RatMage::RatMage(GameEngine* pEngine) : BaseEnemy(pEngine)
{
    sprite = ImageManager::loadImage("resources/Enemies/Ratfolk_Mage.png", true);

    enemyType = 2;

    health = 4;


}

void RatMage::performIdle()
{
    if (idleTime == 0) {
        changeState(Moving);
    }
}

void RatMage::performMoving()
{
    if (ChasePlayer() && attackCD == 0) {

        changeState(Attack);

    }
}

void RatMage::performAttack()
{
    if (spriteMapX == 4 && spriteMapY == 2) {
        MeleeAttack();
        attackCD = 3;
    }
    else if (spriteMapX == 5 && spriteMapY == 2) {
        idleTime = 2;
        changeState(Idle);
    }
}

void RatMage::performHurt()
{
    if (spriteMapX == 3) {
        changeState(Idle);
    }
}

void RatMage::changeState(AnimationState newState)
{
    if (currState == newState) {
        return;
    }

    currState = newState;
    spriteMapX = 0;

    switch (currState) {
    case Idle:
        spriteMapY = 0;
        animationLength = 8;
        break;

    case Moving:
        spriteMapY = 1;
        animationLength = 8;
        break;

    case Attack:
        spriteMapY = 2;
        animationLength = 6;
        break;
    case SpecialAttack:
        spriteMapY = 3;
        animationLength = 6;
        break;
    case Hurt:
        spriteMapY = 4;
        animationLength = 4;
        break;
    case Dead:
        spriteMapY = 5;
        animationLength = 5;
        break;
    }
}
