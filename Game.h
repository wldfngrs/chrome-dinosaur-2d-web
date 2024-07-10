#pragma once

#include "EntityComponentSystem.h"
#include "ObstacleManager.h"
#include "DirtManager.h"
#include "SoundManager.h"
#include "Text.h"

#include <string>

class Entity;

class Game {
	int initSDL();
	int initFonts();
	int initSounds();
	void initDinoEntity();
	void initNonDinoEntities();
	void initObstacles();

	void resetNonDinoEntities();
	void resetDinoEntity();
	void resetObstacles();

	bool mInLobby;
	bool mGameOverScreen;
	bool mGameCompletedScreen;
	bool mTitleScreen;
	bool mMainGameplay;

	bool mPlayerQuit;
	bool mPlayerFail;
	bool mInitDone;

	std::string mGameOverMessage;
	std::string mInitErrorMessage;

	SDL_Window* mGameWindow;
	ObstacleManager mObstacleManager;
	TextManager mTextManager;
	DirtManager mDirtManager;

public:
	Game();
	~Game();

	void render();
	void update();
	void loop();
	void resetGame();
	void handleEvents();

	bool initializationDone() const;
	bool playerHasQuit() const;
	bool playerHasFailed() const;

	TextManager& getTextManager();


	static bool mSpeedToggled;
	static bool mObstacleSpeedToggled;
	static bool mGameCompleted;

	static int mTick;
	static SDL_Event mEvent;
	static SDL_Renderer* mGameRenderer;
	static EntityManager mEntityManager;
	static SoundManager mSoundManager;

	static int mSCREEN_WIDTH;
	static int mSCREEN_HEIGHT;

	static Entity& mDino;
};