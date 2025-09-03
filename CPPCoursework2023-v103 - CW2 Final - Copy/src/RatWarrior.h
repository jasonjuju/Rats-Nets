#pragma once
#include "BaseEnemy.h"
class RatWarrior :
    public BaseEnemy
{
public:
    RatWarrior(GameEngine*);

    
    void performIdle() override;

    void performMoving() override;

    virtual void performAttack() override;

    virtual void performHurt() override;
    
    void changeState(AnimationState) override;
};

