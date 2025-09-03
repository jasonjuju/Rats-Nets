#include "PlayerObject.h"
#include "UtilCollisionDetection.h"
#include "GameEngine.h"
#include "GameManager.h"




PlayerObject::PlayerObject(GameEngine* pEngine) : DisplayableObject(pEngine)
{
    engine = pEngine;

    

    playerImage = ImageManager::loadImage("resources/Player/Pyromancer.png", true);
    playerImage.setTransparencyColour(0x000000);

    m_iDrawWidth = 64;
    m_iDrawHeight = 64;
    m_iCurrentScreenX = (1300 - m_iDrawWidth)/2;
    m_iCurrentScreenY = (800 - m_iDrawHeight)/2;


    //Change later, basic rectangle for collision
    collisionBoxTopLeftX = m_iCurrentScreenX+17;
    collisionBoxTopLeftY = m_iCurrentScreenY+51;
    collisionBoxWidth = m_iDrawWidth-34;
    collisionBoxHeight = m_iDrawHeight-51;

    currTime = 0;
}

void PlayerObject::virtDraw()
{
    
    if (!isVisible()) {
        return;
    }
   
    

    //render image into foreground, with the background removed


    map->setXShift(spriteMapX * m_iDrawWidth);
    map->setYShift(spriteMapY * m_iDrawHeight);

    playerImage.renderImageApplyingMapping(engine, engine->getForegroundSurface(),
        m_iCurrentScreenX,
        m_iCurrentScreenY,
        m_iDrawWidth,
        m_iDrawHeight,
        map
    );
    

    

    //FOR DRAWING COLLISION BOX
    //engine->getForegroundSurface()->drawRectangle(collisionBoxTopLeftX, collisionBoxTopLeftY,
    //    collisionBoxTopLeftX + collisionBoxWidth, collisionBoxTopLeftY + collisionBoxHeight,0x0000FF);
    
}


void PlayerObject::virtDoUpdate(int iCurrentTime)
{
    
    if (!isVisible()) {
        return;
    }

    trackCooldowns(iCurrentTime);

    

    if ((iCurrentTime - currTime) >= 100) {
        currTime = iCurrentTime;
        updateSprite();
    }




    checkInput();

    //TODO: Make the following 2 ifs into a function
    if (hitImmune && immunityStart == -1) {
        immunityStart = iCurrentTime;
    }

    if (iCurrentTime - immunityStart > 1000) {

        hitImmune = false;
        immunityStart = -1;
    }


    engine->redrawDisplay();
}


void PlayerObject::hitPlayer(int damage)
{
    if (hitImmune) {
        return;
    }

    health -= damage;

    std::cout << "Damage taken! " << health << " health left.\n";

    hitImmune = true;

    if (health <= 0) {
        killPlayer();
    }
    else {
        canMove = false;
        changeAnimation(Damage);
    }
}

void PlayerObject::killPlayer()
{
    canMove = false;
    changeAnimation(Death);
    deathCD = setOnCooldown(1);
    std::cout << "player dead!\n";

}

void PlayerObject::updateSprite()
{

    //Only update sprite movement if the player is moving
    if (canMove) {

        if (engine->isKeyPressed(SDLK_a)) {
            map->setFlipped(true);
        }
        else if (engine->isKeyPressed(SDLK_d)) {
            map->setFlipped(false);
        }

        if (engine->isKeyPressed(SDLK_w) || engine->isKeyPressed(SDLK_a)
            || engine->isKeyPressed(SDLK_s) || engine->isKeyPressed(SDLK_d)) {
            changeAnimation(Walking);
        }
        else {
            changeAnimation(Idle);
        }
        
    }
    else {
        if (currAnimation == Attack && spriteMapX == 4) {
            canMove = true;
            changeAnimation(Idle);
        }
        else if (currAnimation == Damage && spriteMapX == 3) {
            canMove = true;
            changeAnimation(Idle);
        }
        else if (currAnimation == Death && spriteMapX == 3) {
            isDead = true;
            
        }
    }
        
    
        
    
        


    //Below can be removed later
    if (engine->isKeyPressed(SDLK_t)) {
        changeAnimation(Attack);
    }
    else if (engine->isKeyPressed(SDLK_y)) {
        changeAnimation(SpecialAttack);
    }
    else if (engine->isKeyPressed(SDLK_u)) {
        changeAnimation(Damage);
    }
    else if (engine->isKeyPressed(SDLK_i)) {
        changeAnimation(Death);
    }
    
    //Do not animate if dead
    if (!isDead) {
        spriteMapX = (spriteMapX + 1) % animationLength;
    }
    

}

//Change the animation of the player. could possibly remove currAnimation and just use newState
void PlayerObject::changeAnimation(AnimationState newState) 
{
    if (currAnimation == newState) {
        return;
    }
    

    currAnimation = newState;
    spriteMapX = 0;

    switch (currAnimation) {
    case Idle:
        
        spriteMapY = 0;
        animationLength = 4;
        break;

    case Walking:
        spriteMapY = 4;
        animationLength = 8;
        break;

    case Attack:
        spriteMapY = 2;
        animationLength = 5;
        break;
    case SpecialAttack:
        spriteMapY = 3;
        animationLength = 15;
        break;
    case Damage:
        spriteMapY = 5;
        animationLength = 4;
        break;
    case Death:
        spriteMapY = 6;
        animationLength = 4;
        break;
    }
}

int PlayerObject::setOnCooldown(int cdTime)
{
    return currTime + 1000 * cdTime;
}

//checks whether effects are on cooldown
void PlayerObject::trackCooldowns(int iCurrentTime)
{
    if (iCurrentTime > attackCD && attackCD != 0) {
        attackCD = 0;
    }
    if (iCurrentTime > deathCD && deathCD != -1) {
        engine->getGameManager()->endGame();
    }

}


void PlayerObject::checkInput()
{
    //Cannot attack when hit or dead
    if (currAnimation == Death || currAnimation == Damage) {
        return;
    }


    if (leftClickDown && attackCD == 0) {

        basicAttack(engine->getCurrentMouseX(), engine->getCurrentMouseY());

        leftClickDown = false;
        
    }
    
}

void PlayerObject::createFireball(int targetX, int targetY)
{
    engine->appendObjectToArray(new Fireball(engine, targetX, targetY));

    //Make sure object is behind overlay
    engine->moveToLast(engine->getOverlay());

}

void PlayerObject::basicAttack(int directionX, int directionY)
{
    createFireball(directionX, directionY);
    canMove = false;
    attackCD = setOnCooldown(1);
    changeAnimation(Attack);
    
}




long PlayerObject::virtNotify(int iSignalNumber, int x, int y)
{
    switch (iSignalNumber) {
    
    case 2:
        setVisible(true);
        return 1;
    default:
        setVisible(false);
        return 0;
    }
    return 0;
}
