#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "BaseEntity.h"


class BaseEnemy :
    public BaseEntity
{
    

public:
    BaseEnemy(GameEngine*);
    virtual void virtDraw() override;

    void virtMove(int) override;

    virtual void performIdle() {};

    virtual void performMoving() {};

    virtual void performAttack() {};

    virtual void performSpecialAttack() {};

    virtual void performHurt() {};

    virtual void performDead() {};

    bool ChasePlayer();

    void MeleeAttack();

    void TrackCooldowns(int);

    bool checkInBoundingBox(int x, int y);

    void takeDamage(int damage);

    bool checkImmune();

    void givePoints();

    int getEnemyType() { return enemyType; }


protected:
    
    int health = 5;
    int attackCD = 0;
    int deathTime = 10;
    int idleTime = 0;
    
    bool facingLeft = false;

    int pointValue = 5;

    int enemyType = -1;


private:
    float storeX = 0.0f;
    float storeY = 0.0f;
    int playerX;
    int playerY;
};

