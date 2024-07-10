#pragma once

#include "EntityComponentSystem.h"
#include "Vector2D.h"

struct TransformComponent : public Component {
	Vector2D mPosition;
	Vector2D mVelocity;

	int mHeight = 1;
	int mWidth = 1;

	TransformComponent() {
		mPosition.zero();
		mVelocity.zero();
	}

	TransformComponent(int scale) {
		mPosition.zero();
		mVelocity.zero();
	}

	TransformComponent(float x, float y) {
		mPosition.x = x;
		mPosition.y = y;
		mVelocity.zero();
	}

	TransformComponent(float x, float y, int w, int h) {
		mPosition.x = x;
		mPosition.y = y;
		mHeight = h;
		mWidth = w;
	}

	void init() override {}

	void update() override {
		mPosition.x += mVelocity.x;
		mPosition.y += mVelocity.y;
	}
};