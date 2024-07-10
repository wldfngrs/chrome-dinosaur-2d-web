#pragma once

#include "EntityComponentSystem.h"
#include "TextureManager.h"

#include <cstdarg>

class Sprite;

class SpriteComponent : public Component {
	SDL_Texture* mTexture;
	
	const char* mPathToTexture;

	std::unique_ptr<Sprite> mSprite;

public:
	SpriteComponent(const char* pathToTexture, std::unique_ptr<Sprite> sprite, int x, int y, int w, int h);
	SpriteComponent(const char* pathToTexture);
	~SpriteComponent();

	void init() override;
	void update() override;
	void draw() override;

	void setTexture(const char* pathToTexture);
	
	void setSprite(std::unique_ptr<Sprite> sprite);
	std::unique_ptr<Sprite>& getSprite();
};