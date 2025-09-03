#include "Torch.h"
#include "GameEngine.h"

Torch::Torch(GameEngine* pEngine, int xPos, int yPos) : DisplayableObject(pEngine)
{
	m_iCurrentScreenX = xPos;
	m_iCurrentScreenY = yPos;
	m_iDrawWidth = 64;
	m_iDrawHeight = 64;

	engine = pEngine;

	sprite = ImageManager::loadImage("resources/Campfire.png", true);
}

void Torch::virtDraw()
{
	if (!isVisible()) {
		return;
	}

	sprite.renderImageWithMask(
		engine->getBackgroundSurface(), 
		64 * spriteY, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iDrawWidth, m_iDrawHeight
	);
	
}

void Torch::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible()) {
		return;
	}

	if ((iCurrentTime - currTime) >= 100) {
		currTime = iCurrentTime;
		
		spriteY = (spriteY + 1) % 4;
	}

}

long Torch::virtNotify(int iSignalNumber, int x, int y)
{
	switch (iSignalNumber) {

	case 1:
		setVisible(true);
		return 1;
		break;
	default:
		setVisible(false);
		return 0;
	}
	return 0;
}
