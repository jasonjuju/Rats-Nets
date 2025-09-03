#include "Scoreboard.h"
#include "GameEngine.h"
#include <iomanip>

Scoreboard::Scoreboard(GameEngine* pEngine, int maxX, int maxY, int minX, int minY) :
	maxX(maxX),
	maxY(maxY),
	minX(minX),
	minY(minY),
	engine(pEngine)
{
	drawWidth = maxX - minX;
	drawHeight = maxY - minY;

	font = engine->getFont("resources/pixelEmulator.ttf", 24);


	scoreboardSurface = new DrawingSurface(pEngine);

	scoreboardSurface->createSurface(1300, 800);

	scoreboardSurface->fillSurface(0xFFFFFF);

	drawAllLines();

	drawTitles();

	drawNumbers();

	getScores();
	
	drawScores();
}

void Scoreboard::drawBoard()
{
	engine->getForegroundSurface()->copyRectangleFrom(
		scoreboardSurface,
		minX, minY,
		drawWidth, drawHeight
	);

}

void Scoreboard::drawText(int x, int y, const char* text, int colour)
{
	scoreboardSurface->drawFastString(
		minX + x,
		minY + y,
		text,
		colour,
		font);
}

void Scoreboard::setText(int x, int y, const char* text)
{
	int xPos = 0;
	int yPos = 20 + (int)gapAcross*(y);

	switch (x%3) {
	case 0:
		xPos = 42;
		break;
	case 1:
		xPos = 142;
		break;
	case 2:
		xPos = 327;
	}

	if (x / 3 == 1) {
		xPos += (int)vertSplit;
	}

	drawText(xPos, yPos, text, 0x000000);
}

void Scoreboard::drawTitles()
{
	drawText(12, 20, "RANK", 0x000000);
	drawText(12 + (int)vertSplit, 20, "RANK", 0x000000);

	setText(1, 0, "PLAYER");
	setText(4, 0, "PLAYER");

	drawText(352, 20, "SCORE", 0x000000);
	drawText(352 + (int)vertSplit, 20, "SCORE", 0x000000);

}

//Draw numbers
void Scoreboard::drawNumbers()
{
	std::string stringNum;
	for (int i = 0; i < 10; i++) {
		stringNum = std::to_string(i+1) + ".";
		if (i / 5) {
			setText(3, i % 5 + 1, stringNum.c_str());
		}
		else {
			setText(0, i % 5 + 1, stringNum.c_str());
		}
	}
}

void Scoreboard::drawLineAcross(double y)
{
	scoreboardSurface->mySDLLockSurface();
	scoreboardSurface->drawThickLine(minX, minY + y, maxX-2, minY + y, 0x000000, 3);
	scoreboardSurface->mySDLUnlockSurface();
}

void Scoreboard::drawLineVert(double x)
{
	scoreboardSurface->mySDLLockSurface();
	scoreboardSurface->drawThickLine(minX + x, minY, minX + x, maxY - 2, 0x000000, 3);
	scoreboardSurface->mySDLUnlockSurface();
}

//Create scoreboard grid by drawing lines
void Scoreboard::drawAllLines()
{
	gapAcross = drawHeight / 6;

	for (int i = 1; i < 6; i++) {
		drawLineAcross(i * gapAcross); 
	}

	//Split grid down middle
	vertSplit = drawWidth / 2;

	scoreboardSurface->mySDLLockSurface();
	scoreboardSurface->drawThickLine(minX + vertSplit, minY, minX + vertSplit, maxY - 2, 0x000000, 6);
	scoreboardSurface->mySDLUnlockSurface();

	//Split each section into 1/5, 2/5 and 2/5
	drawLineVert(drawWidth/10);
	drawLineVert(drawWidth/10*3);

	drawLineVert(vertSplit + drawWidth / 10);
	drawLineVert(vertSplit + drawWidth / 10 * 3);

}

void Scoreboard::getScores()
{
	ifstream readFile("scores.csv");

	string currLine;


	//stores all values from the file in a vector
	while (getline(readFile, currLine)) {

		istringstream lineSS(currLine);

		string name;
		string score;


		if (getline(lineSS, name, ',') && getline(lineSS, score, ',')) {



			playerList.push_back({ name, score });

		}
		
	}


	readFile.close();

	
}

void Scoreboard::drawScores()
{

	string stringScore;
	

	//setText(2, 1, test.str().c_str());

	for (int i = 0; i < 10; i++) {

		//Using a stringstream to fill blank spaces with zeros (always 8 char width)
		stringstream displayScore;
		displayScore << setw(8) << setfill('0') << playerList.at(i).score;

		//Convert back to string
		stringScore = displayScore.str();

		if (i / 5 == 1) {
			setText(4, i%5 + 1 , playerList.at(i).name.c_str());
			setText(5, i%5 + 1 , stringScore.c_str());
		}
		else {
			setText(1, i%5 + 1 , playerList.at(i).name.c_str());
			setText(2, i%5 + 1 , stringScore.c_str());
		}
	}
}
