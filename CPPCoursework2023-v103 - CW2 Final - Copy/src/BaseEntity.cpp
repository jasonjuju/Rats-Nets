#include "BaseEntity.h"
#include "GameEngine.h"
#include "BackgroundTileObject.h"

BaseEntity::BaseEntity(GameEngine* pEngine) : DisplayableObject(pEngine),
BASE_SPEED(2)
{
	
	engine = pEngine;

	background = pEngine->getBackground();

	player = pEngine->getPlayer();

	m_iDrawWidth = 64;
	m_iDrawHeight = 64;
	
	
	
}

void BaseEntity::virtDoUpdate(int iCurrentTime)
{
	if (markForDeletion) {
		engine->removeDisplayableObject(this);
		engine->drawableObjectsChanged();
		delete this;
		return;
	}

	if (!isVisible()) {
		return;
	}


	//Change sprite every 100 frames
	if ((iCurrentTime - currTime) >= 100) {
		currTime = iCurrentTime;
		if (!isDead) {
			updateSprite();
		}
	}

	std::srand(iCurrentTime);

	//Reduces the number of times the character is drawn
	//This is needed for smoother movement
	if (iCurrentTime % 100 / 10 % 2 < 6) {
		virtMove(iCurrentTime);
		
	}

	


	matchBackgroundMovement(background->getPlayerAgainstWall());


	

    getEngine()->redrawDisplay();
}

//Moves the same amount as the background, so it stays in the same place relatively
void BaseEntity::matchBackgroundMovement(int againstWall)
{
	//if player can't move, skip all this
	if (player->getCanMove()) {
		//Check whether key is pressed, and whether player is against that wall
		if (getEngine()->isKeyPressed(SDLK_w) && againstWall != 0)
			m_iCurrentScreenY += BASE_SPEED;
		if (getEngine()->isKeyPressed(SDLK_s) && againstWall != 1)
			m_iCurrentScreenY -= BASE_SPEED;
		if (getEngine()->isKeyPressed(SDLK_a) && againstWall != 2)
			m_iCurrentScreenX += BASE_SPEED;
		if (getEngine()->isKeyPressed(SDLK_d) && againstWall != 3)
			m_iCurrentScreenX -= BASE_SPEED;
	}
	
}


long BaseEntity::virtNotify(int iSignalNumber, int x, int y)
{
	switch (iSignalNumber) {
	
	case 2:
		cout << "STILL HERE" << endl;
		setVisible(true);
		return 1;
		break;
	case 10:
		markForDeletion = true;
		
		cout << "GOODBYE" << endl;
		break;
	default:
		setVisible(false);
		return 0;
	}
    return 0;
}
