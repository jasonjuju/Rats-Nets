#include "Fireball.h"

Fireball::Fireball(GameEngine* pEngine, int targetX, int targetY) : BaseRangedAttack(pEngine, targetX, targetY)
{
	sprite = ImageManager::loadImage("resources/Player/fireball.png", true);

    damage = 2;
    shotSpeed = 3;

    currState = Cast;
    spriteMapY = 0;
    animationLength = 4;
}

void Fireball::performCast()
{
    if (spriteMapX == 3) {
        changeState(Flying);
    }
}


void Fireball::performHit()
{
    
    if (spriteMapX == 3) {

        markForDeletion = 1;
    }
}

void Fireball::changeState(RangedAttackState newState)
{
    if (currState == newState) {
        return;
    }

    currState = newState;
    spriteMapX = 0;

    switch (currState) {
    case Cast:
        spriteMapY = 0;
        animationLength = 4;
        break;
    case Flying:
        spriteMapY = 2;
        animationLength = 3;
        break;
    case Hit:
        spriteMapY = 1;
        animationLength = 4;
        break;
    }
}


