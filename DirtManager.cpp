#include "DirtManager.h"
#include "TextureManager.h"
#include "Game.h"

#include <random>

bool DirtManager::positionIsOccupied(int i, int x, int y, int dirtWidth) {
	int index = 0;
	for (const auto& dirt : mDirt) {
		if (i == index) {
			continue;
		}

		if (x + dirtWidth >= dirt.x
			&&
			dirt.x + dirt.mWidth >= x
			&&
			y + mDirtHeight >= dirt.y
			&&
			dirt.y + mDirtHeight >= y)
		{
			return true;
		}

		index++;
	}

	return false;
}

void DirtManager::setTexture() {
	mTexture = TextureManager::loadSpriteTexture("Assets/textures/GroundSheet.png");
}

void DirtManager::setRect(SDL_Rect& rect, int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void DirtManager::init() {
	setTexture();
	setRect(mSrcRectGround, 0, 0, 96, 16);
	setRect(mSrcRectDirt, 0, 16, 16, 16);

	setRect(mDestRectGround, 0, Game::mSCREEN_HEIGHT - 80, Game::mSCREEN_WIDTH, 80);

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> yDistr(Game::mSCREEN_HEIGHT - 80, Game::mSCREEN_HEIGHT - 50);
	std::uniform_int_distribution<> xDistr(0, Game::mSCREEN_WIDTH - 30);

	for (int i = 0; i < 50; i++) {
		int x = xDistr(gen);
		int y = yDistr(gen);

		int len = generateDirtLen(x);

		while (positionIsOccupied(i, x, y, len)) {
			x = xDistr(gen);
			y = yDistr(gen);
			len = generateDirtLen(x);
		}

		mDirt.emplace_back(x, y, len);
	}
}

void DirtManager::update() {
	mDirtVelocity = static_cast<float>(Game::mObstacleSpeedToggled ? -15 : -10);

	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_int_distribution<> yDistr(Game::mSCREEN_HEIGHT - 80, Game::mSCREEN_HEIGHT - 50);
	
	int i = 0;

	for (auto& dirt : mDirt) {
		if (dirt.x <= -dirt.mWidth) {
			dirt.x = Game::mSCREEN_WIDTH - dirt.mWidth;
			dirt.y = yDistr(gen);
		}
		else {
			if (!positionIsOccupied(i, dirt.x + mDirtVelocity, dirt.y, dirt.mWidth)) {
				dirt.x += mDirtVelocity;
			}
		}

		i++;
	}
}

void DirtManager::draw() {
	TextureManager::drawSprite(mTexture, mSrcRectGround, mDestRectGround);

	for (auto& dirt : mDirt) {
		setRect(mDestRectDirt, dirt.x, dirt.y, dirt.mWidth, mDirtHeight);

		TextureManager::drawSprite(mTexture, mSrcRectDirt, mDestRectDirt);
	}
}

int DirtManager::generateDirtLen(int seed) {
	int len(0);
	if (seed <= 400) {
		len = 10;
	}
	else if (seed <= 800) {
		len = 15;
	}
	else {
		len = 20;
	}

	return len;
}