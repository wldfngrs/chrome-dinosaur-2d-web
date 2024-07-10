#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "Sprites.h"
#include "Game.h"
#include "Score.h"

void Background::init() {
	setAnimation(1, 2, 500);

	mAnimationIndex = 1;
	mSwitchTick = 0;
	mSwitchCap = 350;
}

void Background::update() {
	if (Game::mTick % 7 == 0) {
		mSwitchTick++;
	}
	
	if (mSwitchTick >= mSwitchCap) {
		mSwitchTick = 0;

		switch (mAnimationIndex) {
			case 0: {
				if (Game::mSpeedToggled) {
					setAnimation(mAnimationIndex, 2, 200);
				}
				else {
					setAnimation(mAnimationIndex, 2, 500);
				}

				Game::mSoundManager.playMusic(NIGHT_MUSIC);

				mAnimationIndex = 1;
				mSwitchCap = 200;
				break;
			}
			case 1: {
				if (Game::mSpeedToggled) {
					setAnimation(mAnimationIndex, 2, 200);
				}
				else {
					setAnimation(mAnimationIndex, 2, 500);
				}

				if (Game::mSoundManager.getCurrentPlayingMusic() == NIGHT_MUSIC) {
					Game::mSoundManager.playMusic(MORNING_MUSIC);

					mAnimationIndex = 1;
					mSwitchCap = 350;
				}
				else if (Game::mSoundManager.getCurrentPlayingMusic() == MORNING_MUSIC) {
					Game::mSoundManager.playMusic(NOON_MUSIC);

					mAnimationIndex = 0;
					mSwitchCap = 350;
				}

				break;
			}
		}
	}

	SDL_Rect& rSrcRect = getSrcRect();

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}

void Background::resetTick() {
	mSwitchTick = 0;
	mAnimationIndex = 1;
}

void CelestialBody::update() {
	TransformComponent& rTransform = getTransform();

	rTransform.mVelocity.x = -3;

	if (rTransform.mPosition.x <= -rTransform.mWidth) {
		rTransform.mPosition.x = static_cast<float>(Game::mSCREEN_WIDTH);
		rTransform.mVelocity.x = Game::mSpeedToggled ? (float)(- 15) : (float)(-3);
	}
}