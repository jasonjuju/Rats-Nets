#include "RatWarrior.h"


RatWarrior::RatWarrior(GameEngine* pEngine) : BaseEnemy(pEngine)
{
    sprite = ImageManager::loadImage("resources/Enemies/Ratfolk_Warrior.png", true);

    enemyType = 1;

}

void RatWarrior::performIdle()
{
    if (idleTime == 0) {
        changeState(Moving);
    }
}

void RatWarrior::performMoving()
{
    if (ChasePlayer() && attackCD == 0) {
        
        changeState(Attack);
        
    }
}

void RatWarrior::performAttack()
{
    if (spriteMapX == 3 && spriteMapY == 2) {
        MeleeAttack();
        attackCD = 3;
    }
    else if (spriteMapX == 6 && spriteMapY == 2) {
        idleTime = 2;
        changeState(Idle);
    }

    
}

void RatWarrior::performHurt()
{
    if (spriteMapX == 3) {
        changeState(Idle);
    }
}


void RatWarrior::changeState(AnimationState newState)
{
    
    if (currState == newState) {
        return;
    }
    
    currState = newState;
    spriteMapX = 0;

    switch (currState) {
    case Idle:
        spriteMapY = 0;
        animationLength = 4;
        break;

    case Moving:
        spriteMapY = 1;
        animationLength = 8;
        break;

    case Attack:
        spriteMapY = 2;
        animationLength = 7;
        break;
    case SpecialAttack:
        spriteMapY = 3;
        animationLength = 8;
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
