#pragma once

#include "States.h"
#include "Sprites.h"
#include "SoundManager.h"
#include "Game.h"

class RunningState : public DinoState {
	void enter(Dino& dino) override {
		dino.setSrcRect(0, 0, 32, 32);

		Collider& rCollider = dino.getCollider();
		TransformComponent& rTransform = dino.getTransform();

		rTransform.mPosition.y = static_cast<float>(263);

		rCollider.resize(1);
		rCollider.setColliderRect(0, rTransform.mPosition.x, rTransform.mPosition.y + 30, 121, 113);
		
		if (Game::mSpeedToggled) {
			dino.setAnimation(0, 2, 150);
		}
		else {
			dino.setAnimation(0, 2, 200);
		}

		dino.startRun();
	}

	void update(Dino& dino) override {
		SDL_Rect& rSrcRect = dino.getSrcRect();

		rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / dino.getFramesSpeed()) % dino.getFramesCount());
		rSrcRect.y = dino.getSheetIndex() * rSrcRect.h;
	}

	void leave(Dino& dino) override {
		dino.stopRun();
	}
};

class DuckingState : public DinoState {
	void enter(Dino& dino) override {
		dino.setSrcRect(0, 64, 32, 32);

		Collider& rCollider = dino.getCollider();
		TransformComponent& rTransform = dino.getTransform();

		rTransform.mPosition.y = static_cast<float>(263);

		rCollider.resize(1);
		rCollider.setColliderRect(0, rTransform.mPosition.x, rTransform.mPosition.y + 68, 140, 128);

		if (Game::mSpeedToggled) {
			dino.setAnimation(2, 2, 150);
		}
		else {
			dino.setAnimation(2, 2, 200);
		}

		dino.startDuck();
	}

	void update(Dino& dino) override {
		SDL_Rect& rSrcRect = dino.getSrcRect();

		rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / dino.getFramesSpeed()) % dino.getFramesCount());
		rSrcRect.y = dino.getSheetIndex() * rSrcRect.h;
	}

	void leave(Dino& dino) override {
		dino.stopDuck();
	}
};

class JumpingState : public DinoState {
	bool mCharging = false;
	int mChargeTime = 0;
	int mMAX_CHARGETIME = 5;

	bool mLanding = false;
	int mLandTime = 0;
	int mMAX_LANDTIME = 13;

	bool mJumping = false;
	int mJumpTime = 0;
	int mMAX_JUMPTIME = 30;

public:
	void enter(Dino& dino) override {
		dino.setSrcRect(0, 32, 32, 32);

		TransformComponent& rTransform = dino.getTransform();
		Collider& rCollider = dino.getCollider();

		rCollider.resize(1);
		rCollider.setColliderRect(0, rTransform.mPosition.x + 4, rTransform.mPosition.y + 38, 130, 96);

		mCharging = true;

		dino.startJump();
	}

	void update(Dino& dino) override {
		if (mCharging) {
			mChargeTime++;

			if (mChargeTime >= mMAX_CHARGETIME) {


				mChargeTime = 0;
				mCharging = false;
				mJumping = true;

				TransformComponent& rTransform = dino.getTransform();
				Collider& rCollider = dino.getCollider();

				dino.setSrcRect(32, 32, 32, 32);

				rTransform.mPosition.y -= dino.mVerticalJumpDistance;

				rCollider.resize(1);
				rCollider.setColliderRect(0, rTransform.mPosition.x, rTransform.mPosition.y + 32, 124, 68);
			}
		}


		if (mJumping) {
			mJumpTime++;

			if (mJumpTime >= mMAX_JUMPTIME) {
				mJumpTime = 0;
				mJumping = false;
				mLanding = true;
				dino.setSrcRect(64, 32, 32, 32);

				TransformComponent& rTransform = dino.getTransform();
				Collider& rCollider = dino.getCollider();

				rTransform.mPosition.y += dino.mVerticalJumpDistance;

				rCollider.resize(1);
				rCollider.setColliderRect(0, rTransform.mPosition.x, rTransform.mPosition.y + 157, 155, 19);
			}
		}

		if (mLanding) {
			mLandTime++;

			if (mLandTime >= mMAX_LANDTIME) {
				mLanding = false;
				mLandTime = 0;
				leave(dino);
			}
		}
	}

	void leave(Dino& dino) override {
		dino.stopJump();
		dino.clearState();
		dino.setState(new RunningState());
		dino.getState()->enter(dino);
	}
};