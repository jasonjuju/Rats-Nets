#include "GameManager.h"
#include "GameEngine.h"
#include "UtilCollisionDetection.h"
#include <iostream>
#include <fstream>

GameManager::GameManager(GameEngine* pEngine) : DisplayableObjectContainer(1) {
	createObjectArray(0);
	engine = pEngine;
	player = engine->getPlayer();
	background = engine->getBackground();
}

//Add an Object to the manager and engine
void GameManager::addEntity(BaseEntity* object)
{
	engine->appendObjectToArray(object);
	appendObjectToArray(object);
	engine->moveToLast(engine->getPlayer());
	engine->moveToLast(engine->getOverlay());
}

//Remove an object from manager and engine, then delete it
void GameManager::removeEntity(BaseEntity* object)
{
	removeDisplayableObject(object);
}

void GameManager::removeAllEntities()
{
	drawableObjectsChanged();
	for (int i = 0; i < m_vecDisplayableObjects.size(); i++)
	{
		DisplayableObject* obj = m_vecDisplayableObjects[i];
		engine->removeDisplayableObject(obj);
		
	}
}

bool GameManager::checkValidPosition(int xPos, int yPos)
{
	return !CollisionDetection::checkCircles(xPos, yPos, player->getPlayerX(), player->getPlayerY(), 200);
}



//Summon a single enemy (type determined by int given)
void GameManager::summon(int type)
{
	bool isValid = false;

	int xPos;
	int yPos;

	//generate random positions until you have a valid pair
	while (!isValid) {
		int random = std::rand();

		xPos = 1 + random / ((RAND_MAX + 1u) / 1300);

		random = std::rand();

		yPos = 1 + random / ((RAND_MAX + 1u) / 800);

		isValid = checkValidPosition(xPos, yPos);
	}
	


	BaseEnemy* newEnemy;

	int random2 = std::rand() % 10;

	if (random2 < mageChance * 10) {
		newEnemy = new RatMage(engine);
	}
	else {
		newEnemy = new RatWarrior(engine);
	}


	newEnemy->setPosition(xPos, yPos);

	addEntity(newEnemy);
	
}

void GameManager::summonWave(int time)
{

	for (int i = 0; i < spawnNumber; i++) {
		if (getContentCount() < maxSpawns) {
			summon(1);
		}
	}

	//Check wave strength every 10 seconds
	if (time % 10 == 0) {
		checkWave(time);
	}
}

void GameManager::checkWave(int time)
{
	if (time < 10) {
		waveStrength = 0;
	}
	else if (time < 30) {
		waveStrength = 1;
	}
	else if (time < 60) {
		waveStrength = 2;
	}
	else if (time < 120) {
		waveStrength = 3;
	}
	else {
		waveStrength = 4;
	}

	updateWaveStrength();
}

//Determines strength of the wave
void GameManager::updateWaveStrength()
{
	switch (waveStrength) {
	case 0:
		spawnNumber = 1;
		maxSpawns = 4;
		mageChance = 0.0;
		break;
	case 1:
		spawnNumber = 2;
		maxSpawns = 8;
		mageChance = 0.2;
		break;
	case 2:
		spawnNumber = 3;
		maxSpawns = 12;
		mageChance = 0.3;
		break;
	case 3:
		spawnNumber = 4;
		maxSpawns = 16;
		mageChance = 0.4;
		break;
	case 4:
		spawnNumber = 5;
		maxSpawns = 22;
		mageChance = 0.6;
		break;
	}
	
}

//Check collision with projectile
void GameManager::checkAllCollisions(BaseRangedAttack* attack, int x, int y)
{
	
	BaseEnemy* enemy;

	//For all objects, check their if their x and y are close, if they are, check collision
	for (DisplayableObject* ptr : m_vecDisplayableObjects) {

		//This should not cause problems, as all objects in this array are enemies
		enemy = dynamic_cast<BaseEnemy*>(ptr);


		//check if colliding
		if (enemy->checkInBoundingBox(x, y)) {
			if (!enemy->checkImmune()) {
				//do damage to enemy
				enemy->takeDamage(attack->getDamage());
				//Change state to hit
				attack->changeState(BaseRangedAttack::RangedAttackState::Hit);
			}
		}
		
	}

	
}

void GameManager::addPoints(int value)
{
	points += value;
}

void GameManager::endGame()
{
	//Remove any entities still in the game
	//Notify all objects in the engine that the game is over, this will delete the enemies
	removeAllEntities();
	engine->notifyAllObjects(10);

	engine->changeStateGiveValue(4, points);

}

void GameManager::saveGameAndExit()
{


	ofstream saveState("SavedGame.csv");

	
	//BACKGROUND
	saveState << "BACKGROUND" << ',';

	//Map code
	saveState << background->getMap() << ',';

	//Coords for tiles
	saveState << background->getXCoord() << ',';
	saveState << background->getYCoord() << ',';

	//Offset on tiles
	saveState << background->getXOffset() << ',';
	saveState << background->getYOffset() << endl;



	//PLAYER
	saveState << "PLAYER" << ',';

	//Player's current health
	saveState << player->getHealth() << endl;

	

	std::for_each(
		m_vecDisplayableObjects.begin(), m_vecDisplayableObjects.end(), 
		[&](DisplayableObject* pObj) 
		{ 

			if (pObj == nullptr) return;

			BaseEnemy* enemy = dynamic_cast<BaseEnemy*>(pObj);
			 
			//ENEMY
			saveState << "ENEMY" << ',';

			//Type
			saveState << enemy->getEnemyType() << ',';

			//Position on screen
			saveState << enemy->getDrawingRegionLeft() << ',';
			saveState << enemy->getDrawingRegionTop() << endl;
		});


	saveState.close();
}

//Load game from saved game
void GameManager::loadGame()
{
	


	//load game for reading
	ifstream loadState("SavedGame.csv");

	if (!loadState.is_open()) {
		return;
	}


	string type;

	string mapCode;
	string xCoord;
	string yCoord;
	string xOffset;
	string yOffset;

	//Check whether first line store the background
	//If not, this save isn't valid, so we return before doing anything
	if (getline(loadState, type, ',')) {
		if (type != "BACKGROUND") {
			//Closing file if we return
			loadState.close();
			return;
		}

	}

	if (getline(loadState, mapCode, ',') &&
		getline(loadState, xCoord, ',') &&
		getline(loadState, yCoord, ',') &&
		getline(loadState, xOffset, ',') &&
		getline(loadState, yOffset))
	{


		//Set the map
		background->setBackground(stoi(mapCode));


		//Set position of the background
		background->setXCoord(stoi(xCoord));
		background->setYCoord(stoi(yCoord));
		background->setXOffset(stoi(xOffset));
		background->setYOffset(stoi(yOffset));


		//refresh background to draw correct tiles
		background->redrawTiles();
	}	

	
	string line;

	while (getline(loadState, line)) {
		istringstream lineSS(line);

		//Get the type to check what needs loading
		if (getline(lineSS, type, ',')) {

			if (type == "PLAYER") {
				string health;

				if (getline(lineSS, health, ',')) {
					//load player's health
					player->setHealth(stoi(health));
				}

			}
			else if (type == "ENEMY") {
				string enemyType;
				string xPos;
				string yPos;

				BaseEnemy* enemy;

				if (getline(lineSS, enemyType, ',') &&
					getline(lineSS, xPos, ',') &&
					getline(lineSS, yPos, ',')){

					//based on type, create a new enemy
					switch (stoi(enemyType)) {
						case 1:
							enemy = new RatWarrior(engine);
							break;
						//If type unrecognised, close to prevent any errors
						default:
							cout << "Error: enemy type not recognised, returning\n";
							loadState.close();
							return;
					}

					enemy->setPosition(stoi(xPos), stoi(yPos));

					addEntity(enemy);

				}
			}
			//If type is unrecognised, close the file and return
			else {
				cout << type << "Error: unexpected line in load file\n";
				loadState.close();
				return;
			}

		}
	}


	loadState.close();
}

void GameManager::startGame()
{
	//Reset background
	background->setXCoord(0);
	background->setYCoord(0);
	background->redrawTiles();

	//Remove all enemies
	destroyOldObjects(true);

	//reset player

	//Change state to running
	engine->changeState(2);

	//Set enemy spawner to beginning
}





