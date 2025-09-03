#include "BackgroundTileObject.h"
#include "GameEngine.h"

BackgroundTileObject::BackgroundTileObject(GameEngine* pEngine) 
	: BaseEntity(pEngine),
	TILE_GRID_WIDTH(23),
	TILE_GRID_HEIGHT(15),
	pixelBuffer(new DrawingSurface(pEngine))
{
	player = pEngine->getPlayer();
	xCoord = 0;
	yCoord = 0;


	pixelBuffer->createSurface((TILE_GRID_WIDTH * 64), (TILE_GRID_HEIGHT * 64));

	//Remove filter, so that the pixels can be drawn off screen
	pixelBuffer->setDrawPointsFilter(NULL);

	
	

	tileGrid.setTopLeftPositionOnScreen(m_iCurrentScreenX,
		m_iCurrentScreenY);

	tileWallGrid.setTopLeftPositionOnScreen(m_iCurrentScreenX,
		m_iCurrentScreenY);

	


	int random = std::rand();

	//Randomly choose what map is loaded
	map = 1 + random / ((RAND_MAX + 1u) / 2);

	setBackground(map);


	//Colour of background (where no tiles are)
	pixelBuffer->fillSurface(0x2F2F2E);


	for (int i = 0; i < TILE_GRID_WIDTH; i++) {
		for (int j = 0; j < TILE_GRID_HEIGHT; j++) {
			tileGrid.setMapValue(i, j, (mapCodes.at(j)).at(i));
		}
	}

	tileGrid.drawAllTiles(getEngine(), pixelBuffer);


	for (int i = 0; i < TILE_GRID_WIDTH; i++) {
		for (int j = 0; j < TILE_GRID_HEIGHT; j++) {
			tileWallGrid.setMapValue(i, j, (mapWallCodes.at(j)).at(i));
		}
	}

	tileWallGrid.drawAllTiles(getEngine(), pixelBuffer);

	

}

void BackgroundTileObject::virtDraw()
{
	if (!isVisible()) {
		return;
	}

	getEngine()->getBackgroundSurface()->copyRectangleFrom(
		pixelBuffer, 
		0, 0, 
		(TILE_GRID_WIDTH * 64), (TILE_GRID_HEIGHT * 64), 
		64-m_iCurrentScreenX, 64-m_iCurrentScreenY
	);
	
	
}

//Check for keyboard inputs
void BackgroundTileObject::CheckInput()
{

	//Check whether the player is locked in an animation
	if (player->getCanMove()) {


		if (getEngine()->isKeyPressed(SDLK_w)) {

			if (checkMove(0)) {
				playerAgainstWall = 0;
			}
			else {
				m_iCurrentScreenY += BASE_SPEED;
			}

			if (!checkMove(playerAgainstWall)) {
				playerAgainstWall = -1;
			}
		}
		if (getEngine()->isKeyPressed(SDLK_s)) {

			if (checkMove(1)) {

				playerAgainstWall = 1;
			}
			else {
				m_iCurrentScreenY -= BASE_SPEED;
			}
			if (!checkMove(playerAgainstWall)) {
				playerAgainstWall = -1;
			}
		}
		if (getEngine()->isKeyPressed(SDLK_a)) {

			if (checkMove(2)) {

				playerAgainstWall = 2;

			}
			else {
				m_iCurrentScreenX += BASE_SPEED;
			}
			if (!checkMove(playerAgainstWall)) {
				playerAgainstWall = -1;
			}

		}
		if (getEngine()->isKeyPressed(SDLK_d)) {

			if (checkMove(3)) {

				playerAgainstWall = 3;
			}
			else {
				m_iCurrentScreenX -= BASE_SPEED;
			}
			if (!checkMove(playerAgainstWall)) {
				playerAgainstWall = -1;
			}
		}
		if (getEngine()->isKeyPressed(SDLK_p)) {

			cout << "COllisions TOP " << checkCollision(playerTileMinX, playerTileMinY) << " " << checkCollision(playerTileMaxX, playerTileMinY) << endl;

		}
	}
}


//Called whenever tiles need to be moved in the array 
void BackgroundTileObject::MoveTileGrid()
{
	//Move left
	if (m_iCurrentScreenX >= 64) {
		xCoord--;
	}
	//Move right
	else if (m_iCurrentScreenX <= -64) {
		xCoord++;
	}
	//Move up
	if (m_iCurrentScreenY >= 64) {
		yCoord--;
	}
	//Move down
	else if (m_iCurrentScreenY <= -64) {
		yCoord++;
	}
}



//Checks whether there is a wall at a given coordinate
bool BackgroundTileObject::checkCollision(int x, int y)
{
	int testX = xCoord + (x / 64) + 1;
	int testY = yCoord + (y / 64) + 1;

	if (mapWallCodes.at(testY).at(testX) != -1) {

		switch (mapWallCodes.at(testY).at(testX)) {

		//Left
		case 34:
		case 35:
		case 18:
			if (x % 64 > 48) {
				return false;
			}
			break;
		//Right
		case 32:
		case 37:
		case 16:
			if (x % 64 < 16) {
				return false;
			}
			break;
		//Up
		case 30:
		case 61:
		case 144:
		case 148:
		case 19:
		case 21:
		case 49:
		case 20:
			if (y % 64 > 55) {
				return false;
			}
			break;
		//Down
		case 36:
			if (y % 64 < 55) {
				return false;
			}
			break;
		//Up-Left
		case 50:
			if (y % 64 > 55 || x % 64 > 48) {
				return false;
			}
			break;
		//Up-right
		case 48:
			if (y % 64 > 55 || x % 64 < 16) {
				return false;
			}
			break;
		//left pit
		case 164:
		case 169:
			if (x % 64 > 14) {
				return false;
			}
			break;
		//right pit
		case 160:
		case 165:
			if (x % 64 < 50) {
				return false;
			}
			break;
		//up pit
		case 177:
		case 178:
		case 179:
		case 199:
			if (y % 64 > 14) {
				return false;
			}
			break;
		//down right pit
		case 149:
			if (x % 64 < 50 || y % 64 < 52) {
				return false;
			}
			break;
		case 150:
			if (x % 64 < 50 && y % 64 < 52) {
				return false;
			}
			break;
		//down left pit
		case 152:
			if (x % 64 > 14 && y % 64 < 52) {
				return false;
			}
			break;
		case 153:
			if (x % 64 > 14 || y % 64 < 52) {
				return false;
			}
			break;
		case 176:
		case 198:
		case 181:
			if (x % 64 < 50 || y % 64 > 14) {
				return false;
			}
			break;
		case 182:
			if (x % 64 < 50 && y % 64 > 14) {
				return false;
			}
			break;

		case 184:
			if (x % 64 > 14 && y % 64 > 14) {
				return false;
			}
			break;
		case 180:
		case 200:
		case 185:
			if (x % 64 > 14 || y % 64 > 14) {
				return false;
			}
			break;

		//back of wall
		case 1:
			if (y % 64 < 20) {
				return false;
			}
			break;
		case 0:
			if (y % 64 < 20 || x % 64 < 16) {
				return false;
			}
			break;
		case 2:
			if (y % 64 < 20 || x % 64 > 48) {
				return false;
			}
			break;
	}
		return true;
	}
	else {
		return false;
	}
}

bool BackgroundTileObject::checkHitBoxBounds(int x, int y, int x2, int y2)
{

	if (checkCollision(x, y) || checkCollision(x2, y2)) {
		return true;
	}
	else {
		return false;
	}
}

//Check whether the space being moved to is valid
//TODO: Make collision accurate to wall instead of tile
bool BackgroundTileObject::checkMove(int direction)
{
	int addedSpeedX = 0;
	int addedSpeedY = 0;

	//Calculate where movement should be added
	switch (direction) {
	case -1:
		break;
		//up
	case 0:
		addedSpeedY -= BASE_SPEED;
		break;
		//down
	case 1:
		addedSpeedY += BASE_SPEED;
		break;
		//left
	case 2:
		addedSpeedX -= BASE_SPEED;
		break;
		//right
	case 3:
		addedSpeedX += BASE_SPEED;
		break;
	}

	//create the bounds for the player at this position
	playerTileMinX = player->getHitBoxMinX() - m_iCurrentScreenX + addedSpeedX;
	playerTileMaxX = player->getHitBoxMaxX() - m_iCurrentScreenX + addedSpeedX;
	playerTileMinY = player->getHitBoxMinY() - m_iCurrentScreenY + addedSpeedY;
	playerTileMaxY = player->getHitBoxMaxY() - m_iCurrentScreenY + addedSpeedY;

	
	

	switch (direction) {
	case -1:
		break;
	//up
	case 0:
		if (!checkHitBoxBounds(
			playerTileMinX, playerTileMinY,
			playerTileMaxX, playerTileMinY
		)) 
		{
			return false;
		}
		break;

	//down
	case 1:
		if (!checkHitBoxBounds(
			playerTileMinX, playerTileMaxY,
			playerTileMaxX, playerTileMaxY
		)) 
		{
			return false;
		}
		break;

	//left
	case 2:
		if (!checkHitBoxBounds(
			playerTileMinX, playerTileMinY,
			playerTileMinX, playerTileMaxY
		)) 
		{
			return false;
		}

		break;

	//right
	case 3:
		if (!checkHitBoxBounds(
			playerTileMaxX, playerTileMinY,
			playerTileMaxX, playerTileMaxY
		))
		{
			return false;
		}
		

		break;
	}


	return true;
}






void BackgroundTileObject::setBackground(int mapCode)
{
	cout << mapCode << endl;

	map = mapCode;

	//Empty any previous values before attempting to add more
	mapCodes.clear();
	mapWallCodes.clear();

	string filePath;

	if (mapCode == 1) {
		filePath = "Map1";
	}
	else if (mapCode == 2) {
		filePath = "Map2";
	}
	//If there is an issue, default to map1
	else {
		filePath = "Map1";
	}


	ifstream readFile("resources/Levels/" + filePath + "/tilemap._Floor.csv");

	ifstream readWallFile("resources/Levels/" + filePath + "/tilemap._Walls.csv");


	string currLine;
	string currChar;



	vector<int> mapCodeLine;


	//stores all values from the file in a vector
	while (getline(readFile, currLine)) {
		stringstream lineSS(currLine);

		while (getline(lineSS, currChar, ',')) {
			mapCodeLine.push_back(stoi(currChar));
		}
		mapCodes.push_back(mapCodeLine);

		//Every loop, empty out the vector for the line
		mapCodeLine.clear();
	}

	//Same thing for the Wall map
	while (getline(readWallFile, currLine)) {
		stringstream lineSS(currLine);

		while (getline(lineSS, currChar, ',')) {
			mapCodeLine.push_back(stoi(currChar));
		}
		mapWallCodes.push_back(mapCodeLine);

		//Every loop, empty out the vector for the line
		mapCodeLine.clear();
	}


	mapWidth = mapCodes.at(0).size();

	mapHeight = mapCodes.size();

	readFile.close();

	readWallFile.close();

}

void BackgroundTileObject::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible()) {
		return;
	}

	//Do all input checking here
	CheckInput();
	
	//Checks whether a change is needed to be made
	if (m_iCurrentScreenX % 64 != m_iCurrentScreenX || m_iCurrentScreenY % 64 != m_iCurrentScreenY) {
		//Fill screen with background colour, for any tiles which don't have a value
		pixelBuffer->fillSurface(0x2F2F2E);

		MoveTileGrid();

		redrawTiles();

		m_iCurrentScreenY %= 64;
		m_iCurrentScreenX %= 64;

	}
	

}


//Respond to notification from program
long BackgroundTileObject::virtNotify(int iSignalNumber, int x, int y)
{
	switch (iSignalNumber) {

	case 2:
		setVisible(true);
		return 1;
	default:
		setVisible(false);
		return 0;
	}
	// TODO: Add your implementation code here.
	return 0;
}

//Refresh the tiles on the current screen, can be used if teleported/loaded in 
void BackgroundTileObject::redrawTiles()
{
	pixelBuffer->fillSurface(0x2F2F2E);

	for (int i = 0; i < TILE_GRID_WIDTH; i++)
		for (int j = 0; j < TILE_GRID_HEIGHT; j++) {

			if (coordOutBounds(xCoord + i, yCoord + j)) {
				tileGrid.setMapValue(i, j, -1);
				tileWallGrid.setMapValue(i, j, -1);
			}
			else {
				tileGrid.setMapValue(i, j, (mapCodes.at(yCoord + j)).at(xCoord + i));
				tileWallGrid.setMapValue(i, j, (mapWallCodes.at(yCoord + j)).at(xCoord + i));
			}
		}
		
	tileGrid.drawAllTiles(getEngine(), pixelBuffer);
	tileWallGrid.drawAllTiles(getEngine(), pixelBuffer);
}

