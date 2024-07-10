#pragma once

#include "SDL.h"

#include <map>
#include <string>

enum xPosition {
	CENTERED,
	LEFT,
	RIGHT,
};

enum renderEffect {
	TYPEWRITER,
	INSTANT
};

class TextManager {
	bool mInitDone = false;

	std::map<std::string, SDL_Texture*> mTextCache;

	void addToTextCache_CharByChar(std::string text, const char* fontPath, const int fontIndex, SDL_Color color);
	void addToTextCache_AllAtOnce(std::string text, const char* fontPath, const int fontIndex, SDL_Color color);
	void typeWriterDrawAndRender(std::string lineOfText, int x, int y, size_t w, size_t h);

public:
	~TextManager();

	void init();

	void drawText_Static_NonStatic(std::string text1, std::string text2, xPosition xpos, int y, size_t letterWidth, size_t letterHeight);
	void drawText_Static(std::string text, xPosition xpos, int y, size_t letterWidth, size_t letterHeight, renderEffect effect);
	void drawText_Static(std::string text, int x, int y, size_t letterWidth, size_t letterHeight, renderEffect effect);
	
	void drawText_NonStatic(std::string text, xPosition xpos, int y, size_t letterWidth, size_t letterHeight);
	void drawText_NonStatic(std::string text, int x, int y, size_t letterWidth, size_t letterHeight);
};