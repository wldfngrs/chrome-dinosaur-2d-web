#pragma once

#include "SDL.h"
#include "Vector2D.h"

#include <vector>
#include <utility>

struct Dirt {
	int x;
	int y;
	int mWidth;

	Dirt(int xpos, int ypos, int w) : x(xpos), y(ypos), mWidth(w) {}
};

class DirtManager {
	float mDirtVelocity = -15;

	const int mDirtHeight = 5;

	SDL_Texture* mTexture;

	SDL_Rect mSrcRectGround;
	SDL_Rect mSrcRectDirt;

	SDL_Rect mDestRectGround;
	SDL_Rect mDestRectDirt;

	std::vector<Dirt> mDirt;

	void setRect(SDL_Rect& rect, int x, int y, int w, int h);
	void setTexture();

	int generateDirtLen(int seed);

	bool positionIsOccupied(int i, int x, int y, int dirtWidth);

public:
	void init();
	void update();
	void draw();
};