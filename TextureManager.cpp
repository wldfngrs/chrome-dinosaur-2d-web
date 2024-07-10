#include "TextureManager.h"
#include "SDL_image.h"
#include "Game.h"

SDL_Texture* TextureManager::loadSpriteTexture(const char* pathToTexture) {
	SDL_Surface* tempSurface = IMG_Load(pathToTexture);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::mGameRenderer, tempSurface);
	
	if (texture == nullptr) {
		std::cerr << "[Error] TextureManager::loadSpriteTexture(): '" << pathToTexture << "' SDL_CreateTextureFromSurface() failed!\nDetails: " << SDL_GetError() << "\n\n";
		return nullptr;
	}

	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::drawSprite(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::mGameRenderer, texture, &src, &dest);
}

SDL_Texture* TextureManager::loadTextTexture(std::string textureText, TTF_Font* font, SDL_Color textColor) {
	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::mGameRenderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::drawText(SDL_Texture* texture, int x, int y, size_t w, size_t h) {
	SDL_Rect dest = { x, y, static_cast<int>(w), static_cast<int>(h) };
	SDL_RenderCopy(Game::mGameRenderer, texture, NULL, &dest);
}