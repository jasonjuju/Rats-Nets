#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "BaseEngine.h" 
#include "MirrorImagePixelMapping.h"


class GameManager;
class GameEngine;

class PlayerObject :
    public DisplayableObject
{
public:
    PlayerObject(GameEngine*);

    ~PlayerObject() {
        delete map;
    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;

    long virtNotify(int iSignalNumber, int x, int y) override;


    //calls to get the player's hit box coords
    int getHitBoxMinX() { return collisionBoxTopLeftX; }
    int getHitBoxMaxX() { return collisionBoxTopLeftX + collisionBoxWidth; }
    int getHitBoxMinY() { return collisionBoxTopLeftY; }
    int getHitBoxMaxY() { return collisionBoxTopLeftY + collisionBoxHeight; }

    int getPlayerX() {
        return getXCentre();
        //return m_iCurrentScreenX + m_iDrawWidth/2;
    }

    int getPlayerY() {
        return getYCentre();
        //return m_iCurrentScreenY + m_iDrawHeight/2;
    }

    void hitPlayer(int damage);

    void killPlayer();

    enum AnimationState {
        Idle,
        Walking,
        Attack,
        SpecialAttack,
        Damage,
        Death,
    };

    //Change sprite to next frame
    void updateSprite();

    void changeAnimation(AnimationState);

    //Sets time effect will come off cooldown
    int setOnCooldown(int cdTime);

    //CLEANUP: this could be made better (track time since last used instead of lowering every tick)
    void trackCooldowns(int);

    void virtMouseDown(int iButton, int iX, int iY) override {
        if (!isVisible()) { return; }
        if (iButton == 1) { leftClickDown = true; }
    }

    void virtMouseUp(int iButton, int iX, int iY) override {
        if (!isVisible()) { return; }
        if (iButton == 1) { leftClickDown = false; }
    }

    void checkInput();

    bool getCanMove() { return canMove; }

    void createFireball(int, int);

    void basicAttack(int, int);

    void setFacingLeft(bool left) {
        map->setFlipped(left);
    }

    int getHealth() { return health; }

    void setHealth(int val) { health = val; }

private:
    GameEngine* engine;
    GameManager* gameManager = nullptr;


    

    SimpleImage playerImage;
    int currTime;

    int spriteMapX = 0;
    int spriteMapY = 0;
    int animationLength = 4;

    int collisionBoxTopLeftX = -1;
    int collisionBoxTopLeftY = -1;
    int collisionBoxWidth = -1;
    int collisionBoxHeight = -1;

    int health = 3;

    bool hitImmune = false;

    int immunityStart = -1;

    bool facingLeft = false;

    AnimationState currAnimation = Idle;

    MirrorImagePixelMapping* map = new MirrorImagePixelMapping(spriteMapX * m_iDrawWidth, spriteMapY * m_iDrawHeight, facingLeft);

    bool leftClickDown = false;

    

    bool canMove = true;

    bool isDead = false;


    int attackCD = 0;
    int specialAttackCD = 0;
    //Linger time before end screen
    int deathCD = -1;

};

