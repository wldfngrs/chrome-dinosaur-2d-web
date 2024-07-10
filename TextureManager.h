#pragma once

#include <string>

#include "SDL_ttf.h"

class TextureManager {
public:
	static void drawText(SDL_Texture* texture, int x, int y, size_t w, size_t h);
	static SDL_Texture* loadTextTexture(std::string textureText, TTF_Font* font, SDL_Color textColor);
	
	static SDL_Texture* loadSpriteTexture(const char* pathToTexture);
	static void drawSprite(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};