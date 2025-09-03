#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "MirrorImagePixelMapping.h"

class BackgroundTileObject;

class PlayerObject;

class GameEngine;


class BaseEntity :
    public DisplayableObject
{
public:
    BaseEntity(GameEngine*);
    ~BaseEntity() {
        delete map;
    }

    //Virtual to allow for subtype polymorphism
    void virtual virtDoUpdate(int iCurrentTime) override;

    void matchBackgroundMovement(int againstWall);

    void virtual virtMove(int) {};

    void virtual virtAnimate() {};

    enum AnimationState {
        Idle,
        Moving,
        Attack,
        SpecialAttack,
        Hurt,
        Dead,
    };

    virtual void changeState(AnimationState) {};

    //move the sprite by one
    void updateSprite() { spriteMapX = (spriteMapX + 1) % animationLength; };

    void setDelete(bool del) { 

        markForDeletion = del; }

    void deleteEntity() {
        delete this;
        return;
    }

    int getTopLeftX() {
        return m_iCurrentScreenX;
    }

    int getTopLeftY() {
        return m_iCurrentScreenY;
    }

    long virtNotify(int iSignalNumber, int x, int y) override;

protected:
    GameEngine* engine;

    int const BASE_SPEED;
    BackgroundTileObject* background = nullptr;
    PlayerObject* player =nullptr;

    SimpleImage sprite;

    int currTime = 0;
    int spriteMapX = 0;
    int spriteMapY = 0;
    int animationLength = 1;
    AnimationState currState = Idle;

    bool facingLeft = false;
    MirrorImagePixelMapping* map = new MirrorImagePixelMapping(spriteMapX * m_iDrawWidth, spriteMapY * m_iDrawHeight, facingLeft);

    bool isDead = false;
    bool markForDeletion = false;

};

