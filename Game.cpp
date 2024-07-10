#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "Game.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Collision.h"
#include "SpriteComponent.h"
#include "ObstacleManager.h"
#include "DirtManager.h"
#include "Sprites.h"
#include "Text.h"
#include "Score.h"

#include "SDL_ttf.h"
#include "SDL.h"

#include <sstream>

const int FPS = 60;
const int frameDelay = 1000 / FPS;

int visibilityTick = 0;
bool subtitleIsVisible = true;

Uint32 frameStart;
int frameTime;

int Game::mTick = 0;
int Game::mSCREEN_WIDTH = 900;
int Game::mSCREEN_HEIGHT = 480;

bool Game::mSpeedToggled = false;
bool Game::mObstacleSpeedToggled = false;
bool Game::mGameCompleted = false;

SDL_Event Game::mEvent;
SDL_Renderer* Game::mGameRenderer;
EntityManager Game::mEntityManager;
SoundManager Game::mSoundManager;

Entity& background(Game::mEntityManager.addEntity());
Entity& celestialBody(Game::mEntityManager.addEntity());
Entity& Game::mDino(Game::mEntityManager.addEntity());

Game::Game() {
	if (initSDL() != 0) {
		return;
	}

	if (initFonts() != 0) {
		return;
	}

	if (initSounds() != 0) {
		return;
	}

	initNonDinoEntities();

	initDinoEntity();

	initObstacles();

	Score::init();

	mInitDone = true;

	mTitleScreen = true;
	mInLobby = true;
}

Game::~Game() {
	SDL_DestroyWindow(mGameWindow);
	SDL_DestroyRenderer(mGameRenderer);

	mGameWindow = nullptr;
	mGameRenderer = nullptr;

	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

int Game::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cerr << "[Error] Game::initSDL(): SDL_Init() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	mGameWindow = SDL_CreateWindow("Dino 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mSCREEN_WIDTH, mSCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mGameWindow == nullptr) {
		std::cerr << "[Error] Game::initSDL(): SDL_CreateWindow() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	mGameRenderer = SDL_CreateRenderer(mGameWindow, -1, 0);
	if (mGameRenderer == nullptr) {
		std::cerr << "[Error] Game::initSDL(): SDL_CreateRenderer() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	return 0;
}

int Game::initFonts() {
	if (TTF_Init() < 0) {
		std::cerr << "[Error] Game::initFonts(): TTF_Init() failed!\nDetails: " << TTF_GetError() << "\n";
		return -1;
	}

	mTextManager.init();

	return 0;
}

int Game::initSounds() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		std::cerr << "[Error] Game::initSounds() Couldn't initialize SDL Mixer!\n";
		return -1;
	}

	mSoundManager.init();

	return 0;
}

void Game::initNonDinoEntities() {
	background.addComponent<TransformComponent>(0, 0, Game::mSCREEN_WIDTH, Game::mSCREEN_HEIGHT - 80);
	background.addComponent<SpriteComponent>("Assets/textures/BackgroundSheet.png", std::make_unique<Background>(), 0, 64, 96, 64);

	celestialBody.addComponent<TransformComponent>(Game::mSCREEN_WIDTH, 120, 89, 85);
	celestialBody.addComponent<SpriteComponent>("Assets/textures/Moon.png", std::make_unique<CelestialBody>(), 0, 0, 28, 30);

	mDirtManager.init();
}

void Game::resetNonDinoEntities() {
	TransformComponent* transformComponent = &celestialBody.getComponent<TransformComponent>();
	transformComponent->mPosition.x = static_cast<float>(Game::mSCREEN_WIDTH);

	SpriteComponent* spriteComponent = &background.getComponent<SpriteComponent>();
	spriteComponent->getSprite()->setAnimation(1, 2, 500);

	Background* background = (Background*)spriteComponent->getSprite().get();
	background->resetTick();
}

void Game::initDinoEntity() {
	mDino.addComponent<TransformComponent>(60, 263, 136, 137);
	mDino.addComponent<SpriteComponent>("Assets/textures/DinoSheet.png", std::make_unique<Dino>(), 0, 0, 32, 32);
	mDino.addComponent<KeyboardController>();
}

void Game::resetDinoEntity() {
	SpriteComponent* spriteComponent = &mDino.getComponent<SpriteComponent>();

	spriteComponent->getSprite()->init();
}


void Game::initObstacles() {
	mObstacleManager.init();
}

void Game::resetObstacles() {
	mObstacleManager.reset();
}

void Game::resetGame() {
	Score::reset();

	resetNonDinoEntities();
	resetDinoEntity();
	resetObstacles();

	mPlayerFail = false;
	mSpeedToggled = false;
	mObstacleSpeedToggled = false;

	mTick = 0;
}

static int count = 0;

void Game::handleEvents() {
	SDL_PollEvent(&Game::mEvent);

	switch (mEvent.type) {
	case SDL_QUIT:
		mPlayerQuit = true;
		exit(0);
	case SDL_FINGERDOWN:
	case SDL_KEYDOWN:
		if (mInLobby && (Game::mEvent.type == SDL_FINGERDOWN || Game::mEvent.key.keysym.sym == SDLK_SPACE || Game::mEvent.key.keysym.sym == SDLK_UP)) {
			if (mTitleScreen) {
				mSoundManager.playMusic(MORNING_MUSIC);
			}

			if (mGameOverScreen || mGameCompletedScreen) {
				mSoundManager.playMusic(MORNING_MUSIC);
				resetGame();
			}

			mInLobby = false;
			mGameCompleted = false;
			mGameCompletedScreen = false;
			mGameOverScreen = false;
			mTitleScreen = false;
			mMainGameplay = true;
			count = 0;
			visibilityTick = 0;
			subtitleIsVisible = true;
		}

		break;
	default:
		break;
	}
}

void Game::render() {
	SDL_RenderClear(Game::mGameRenderer);

	mEntityManager.draw();

	mDirtManager.draw();

	Score::draw(*this);

	SDL_RenderPresent(Game::mGameRenderer);
}

void Game::update() {
	mTick++;

	Score::update();

	if (mGameCompleted) {
		mInLobby = true;
		mGameCompletedScreen = true;
		return;
	}

	mObstacleManager.update();

	mEntityManager.refresh();
	mEntityManager.update();

	mDirtManager.update();

	if (Collision::checkForCollisions()) {
		int id = SND_COLLISION;
		mSoundManager.playSound(SND_COLLISION);

		mPlayerFail = true;
		Collision::mCollided = false;
		mGameOverMessage = Collision::getTag();
		mGameOverScreen = true;
		mGameCompletedScreen = false;
		mTitleScreen = false;
		mInLobby = true;
		count = 0;
	}
}

void Game::loop() {
	handleEvents();

	if (mTitleScreen && mInLobby) {
		mInLobby = true;

		if (count == 0) {
			visibilityTick = 0;
			subtitleIsVisible = true;
			SDL_SetRenderDrawColor(Game::mGameRenderer, 0, 0, 0, 0);
		}

		SDL_RenderClear(Game::mGameRenderer);

		mTextManager.drawText_Static("DINO SAUR", CENTERED, Game::mSCREEN_HEIGHT / 7, 40, 60, INSTANT);

		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] or tap to start", CENTERED, 200, 10, 20, INSTANT);
		}

		mTextManager.drawText_Static("a 2D remake of the classic Chrome dinosaur game\nby wldfngrs; https://github.com/wldfngrs", CENTERED, 400, 12, 26, INSTANT);

		if (visibilityTick >= 100) {
			visibilityTick = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}

		SDL_RenderPresent(Game::mGameRenderer);

		count++;
		visibilityTick++;
	}
	else if (mGameOverScreen && mInLobby) {
		if (count == 0) {
			SDL_SetRenderDrawColor(Game::mGameRenderer, 20, 85, 55, 0);

			mSoundManager.playMusic(LOBBY_MUSIC);

			mInLobby = true;

			int currScore = Score::getCurrentScore();

			if (currScore > Score::getHighScore()) {
				Score::setHighScore(currScore);
			}

			mObstacleManager.initGameOverAnimation();

			visibilityTick = 0;
			subtitleIsVisible = true;
		}

		SDL_RenderClear(Game::mGameRenderer);

		mTextManager.drawText_Static_NonStatic("HIGH SCORE: ", std::to_string(Score::getHighScore()), CENTERED, 40, 12, 20);
		mTextManager.drawText_Static_NonStatic("CURRENT SCORE: ", std::to_string(Score::getCurrentScore()), CENTERED, 70, 12, 20);

		mObstacleManager.updateGameOverAnimation();

		mTextManager.drawText_Static(Game::mGameOverMessage, CENTERED, 370, 15, 30, INSTANT);

		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] or tap to run again", CENTERED, 450, 10, 20, INSTANT);
		}

		if (++visibilityTick >= 100) {
			visibilityTick = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}

		SDL_RenderPresent(Game::mGameRenderer);

		count++;
	}
	else if (mGameCompletedScreen && mInLobby) {
		mInLobby = true;

		if (count == 0) {
			mSoundManager.playMusic(LOBBY_MUSIC);

			visibilityTick = 0;
			subtitleIsVisible = true;
		}

		SDL_RenderClear(Game::mGameRenderer);

		mTextManager.drawText_Static("Congratulations! You beat the game!\n"
			"It's no big deal, and certainly no difficult task, yet...\n\n"
			"I appreciate you for playing this long\n"
			"I had fun working on this. I hope you had fun playing as well\n"
			"Have a great day, anon!", CENTERED, 80, 10, 20, INSTANT);

		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] or tap to run again", CENTERED, 400, 10, 20, INSTANT);
		}

		if (++visibilityTick >= 100) {
			visibilityTick = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}

		SDL_RenderPresent(Game::mGameRenderer);

		count++;
	}
	else if (mMainGameplay && !mInLobby) {
		if (count == 0) {
			mSoundManager.playMusic(MORNING_MUSIC);
		}

		update();
		render();

		count++;

		if (mPlayerFail) {
			mGameOverScreen = true;
			count = 0;
		}
		else if (mGameCompleted) {
			mGameCompletedScreen = true;
			count = 0;
		}
	}
}

bool Game::initializationDone() const {
	return mInitDone;
}

bool Game::playerHasQuit() const {
	return mPlayerQuit;
}

bool Game::playerHasFailed() const {
	return mPlayerFail;
}

TextManager& Game::getTextManager() {
	return mTextManager;
}