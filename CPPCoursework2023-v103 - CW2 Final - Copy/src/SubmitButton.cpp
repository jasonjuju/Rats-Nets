#include "SubmitButton.h"
#include "GameEngine.h"

//submits a score to leaderboard
SubmitButton::SubmitButton(GameEngine* pEngine, int x, int y, int width, int height, int points) :
	BaseButton(pEngine, x, y, width, height, "SUBMIT SCORE"),
	score(points)
{
}



void SubmitButton::onClick()
{
	//write score to file
	submitted = true;

}

bool SubmitButton::isSubmitted()
{
	return submitted;
}
