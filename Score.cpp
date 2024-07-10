#include "Score.h"
#include "Game.h"

int Score::mHighscore;
int Score::mCurrentscore;
int Score::mToggleTick = 0;
int Score::mToggleSignal = 1000;
const int Score::mGameCompletedScore = 100000;

void Score::init() {
	mCurrentscore = 1;
	mHighscore = 0;
}

void Score::reset() {
	mCurrentscore = 1;
	mToggleTick = 0;
}

void Score::update() {
	if (Game::mTick % 7 == 0) {
		mCurrentscore++;
		mToggleTick++;
	}

	if (mCurrentscore >= mGameCompletedScore) {
		mCurrentscore = mGameCompletedScore;
		Game::mGameCompleted = true;
		return;
	}

	if (mToggleTick >= mToggleSignal) {
		mToggleTick = 0;

		Game::mSpeedToggled = Game::mSpeedToggled ? false : true;
	
		mToggleSignal = Game::mSpeedToggled ? 300 : 1000;
	}
}

void Score::draw(Game& game) {
	int digitsXPosition = Game::mSCREEN_WIDTH - 8 * 10;
	int highScoreXPosition = Game::mSCREEN_WIDTH - (12 * 10 + 8 * 10);
	int currentScoreXPosition = highScoreXPosition - 30;

	TextManager& rTextManager = game.getTextManager();

	rTextManager.drawText_Static("HIGH SCORE: ", highScoreXPosition, 10, 10, 20, INSTANT);
	rTextManager.drawText_NonStatic(std::to_string(mHighscore), digitsXPosition, 10, 10, 20);
	rTextManager.drawText_Static("CURRENT SCORE: ", currentScoreXPosition, 35, 10, 20, INSTANT);
	rTextManager.drawText_NonStatic(std::to_string(mCurrentscore), digitsXPosition, 35, 10, 20);
}

void Score::setHighScore(int highscore) {
	mHighscore = highscore;
}

int Score::getHighScore() {
	return mHighscore;
}
int Score::getCurrentScore() {
	return mCurrentscore;
}