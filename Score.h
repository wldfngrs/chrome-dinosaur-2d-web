#pragma once

class Game;

class Score {
	static int mHighscore;
	static int mCurrentscore;

	static int mToggleTick;
	static int mToggleSignal;

public:
	Score() = delete;

	static void init();
	static void reset();
	static void update();
	static void draw(Game& game);

	static int getHighScore();
	static int getCurrentScore();

	static void setHighScore(int highscore);

	const static int mGameCompletedScore;
};