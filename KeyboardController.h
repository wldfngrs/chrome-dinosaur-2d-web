#pragma once

#include "EntityComponentSystem.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Sprites.h"

class KeyboardController : public Component {
	SpriteComponent* mSpriteComponent;

public:
	void init() override {
		mSpriteComponent = &mEntity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::mEvent.type == SDL_KEYDOWN) {
			switch (Game::mEvent.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_SPACE:
				mSpriteComponent->getSprite()->press_UP_key();
				break;

			case SDLK_DOWN:
				mSpriteComponent->getSprite()->press_DOWN_key();
				break;
			}
		}

		if (Game::mEvent.type == SDL_FINGERDOWN) {
			mSpriteComponent->getSprite()->press_UP_key();
			return;
		}

		if (Game::mEvent.type == SDL_KEYUP) {
			switch (Game::mEvent.key.keysym.sym) {
			case SDLK_DOWN:
				mSpriteComponent->getSprite()->release_DOWN_key();
				break;
			}
		}
	}
};