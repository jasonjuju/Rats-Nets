#pragma once
#include "header.h"
#include "BaseRangedAttack.h"


class Fireball :
    public BaseRangedAttack
{
public:
    Fireball(GameEngine*, int, int);


    
    void performCast() override;
    void performHit() override;

    void changeState(RangedAttackState) override;

private:

};

