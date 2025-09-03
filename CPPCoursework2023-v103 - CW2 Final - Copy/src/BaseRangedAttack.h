#pragma once
#include "BaseEntity.h"

class BaseRangedAttack :
    public BaseEntity
{
public:
    BaseRangedAttack(GameEngine*, int, int);

    ~BaseRangedAttack() {
        delete projectileMap;
    }

    enum RangedAttackState {
        Cast,
        Flying,
        Hit
    };

    void virtMove(int) override;

    virtual void performCast() {};

    virtual void performFlying();

    virtual void performHit() {};

    void calculateAngle();

    void virtDraw() override;

    virtual void changeState(RangedAttackState) {};

    void fly();

    int getDamage() { return damage; }

protected:
    int damage = 1;
    int shotSpeed = BASE_SPEED;
    int hitRadius = 5;

    float distanceTravelledX = 0;
    float distanceTravelledY = 0;
    float travelDistance = 400;

    float angle = 0;

    int targetX;
    int targetY;

    RangedAttackState currState;

    RotateAndShiftXYImagePixelMapping* projectileMap = new RotateAndShiftXYImagePixelMapping(
        0, 
        0, 
        0);



private:
    float moveAmountX = 0;
    float moveAmountY = 0;
    float storeX = 0.0f;
    float storeY = 0.0f;


};

