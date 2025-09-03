#include "EndDisplay.h"
#include "GameEngine.h"
#include "SubmitButton.h"
#include <iostream>
#include <fstream>
using namespace std;

EndDisplay::EndDisplay(GameEngine* pEngine) :
	BaseDisplay(pEngine)
{
	engine->notifyObjectsAboutKeys(true);

	signalNum = 4;

	font = engine->getFont("Resources/PixelMusketeer.ttf", 60);

	titleFont = engine->getFont("Resources/PixelMusketeer.ttf", 72);

	inputBox = new TextInputBox();


	//Set bounds of display
	minX = (int)(1300 * 0.2);
	minY = (int)(800 * 0.2);
	maxX = (int)(1300 * 0.8);
	maxY = (int)(800 * 0.8);

	exitButton = new ExitButton(engine,
		800, 
		520,
		220,
		100
	);

	exitButton->setSignal(4);
	engine->appendObjectToArray(exitButton);

	submitButton = new SubmitButton(engine,
		280,
		520,
		500,
		100,
		score
	);

	
	submitButton->setSignal(4);
	submitButton->setTextSize(48);
	submitButton->setMarginY(0.2);
	engine->appendObjectToArray(submitButton);


	
	
	
	

}

EndDisplay::~EndDisplay()
{
	delete inputBox;
}



void EndDisplay::virtDraw()
{
	if (!isVisible()) {
		return;
	}

	//Temp background until I get a decent image
	engine->getBackgroundSurface()->drawRectangle(
									minX,
									minY,
									maxX,
									maxY,
									0x003300);

	drawText("GAME OVER", 190, 40, titleFont);


	drawText("SCORE: ", 240, 160, font);

	

	//Convert int to string, then string to const char*
	std::string scoreText = std::to_string(score);

	drawText(scoreText.c_str(), 450, 160, font);

	drawText("Enter Name: ", 100, 250, font);

	drawText(inputBox->GetText(), 470, 250, font);

}

void EndDisplay::virtDoUpdate(int iCurrentTime)
{
	//Delete when ready to be deleted
	if (markForDeletion) {
		engine->removeDisplayableObject(this);
		delete submitButton;
		delete exitButton;
		delete this;
		return;
	}


	if (!isVisible()) {
		return;
	}

	if (submitButton->isSubmitted()) {
		submit();
	}

	redrawDisplay();
}

void EndDisplay::setScore(int value)
{
	score = value;
}




//Tells the engine whether it still needs to check for keyboard inputs
long EndDisplay::virtNotify(int iSignalNumber, int x, int y)
{
	if (iSignalNumber == signalNum) {
		setVisible(true);
		engine->notifyObjectsAboutKeys(true);
		return 1;
	}
	engine->notifyObjectsAboutKeys(false);
	setVisible(false);
	return 0;
}

void EndDisplay::virtKeyDown(int iKeyCode)
{

	if (iKeyCode == SDLK_BACKSPACE || iKeyCode == SDLK_DELETE) {
		inputBox->backspace();
	}
	else if (iKeyCode > 47 && iKeyCode < 58) {
		inputBox->addKey(iKeyCode);
	}
	else if (iKeyCode > 96 && iKeyCode < 123) {
		//if shift is held
		if (engine->isKeyPressed(SDLK_LSHIFT)) {
			inputBox->addKey(iKeyCode - 32);
		}
		else {
			inputBox->addKey(iKeyCode);
		}
	}

}

//Check if score would be on scoreboard, then write leaderboard back as it should be
void EndDisplay::submit()
{
	//Open file for read + write
	//NOT NEEDED change to ifstream
	fstream scoreboard("scores.csv", ios::in | ios::out);

	string line;
	bool scorePlaced = false;
	int lineNum = 0;

	ofstream newScoreboard("newScores.csv");


	//Search scoreboard until we can place the new score
	while (getline(scoreboard, line)  && lineNum < scoreboardLength) {
		istringstream lineSS(line);

		string name;
		string lineScore;


		if (getline(lineSS, name, ',') && getline(lineSS, lineScore, ',')) {


			if (atoi(lineScore.c_str()) < score && !scorePlaced) {
				scorePlaced = true;

				newScoreboard << inputBox->GetText() << ',' << score << endl;
				
				//Account for extra line added
				lineNum++;

			}


			newScoreboard << name << ',' << lineScore << endl;

		}


		lineNum++;
	}

	


	scoreboard.close();
	newScoreboard.close();

	remove("scores.csv");

	//Output error if failed to find file
	if (rename("newScores.csv", "scores.csv")) {
		cout << "Error: could not rename newScores.csv" << endl;
	}

	//Change to scores screen
	engine->changeState(5);
}
