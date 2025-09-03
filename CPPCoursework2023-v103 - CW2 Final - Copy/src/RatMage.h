#pragma once
#include "BaseEnemy.h"
class RatMage :
    public BaseEnemy
{
public:
    RatMage(GameEngine* pEngine);


    void performIdle() override;

    void performMoving() override;

    virtual void performAttack() override;

    virtual void performHurt() override;

    void changeState(AnimationState) override;
};

