#include <memory>

#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Sprites.h"

SpriteComponent::SpriteComponent(const char* pathToTexture, std::unique_ptr<Sprite> sprite, int x, int y, int w, int h) {
	setSprite(std::move(sprite));

	mSprite->setSrcRect(x, y, w, h);

	setTexture(pathToTexture);
}

SpriteComponent::SpriteComponent(const char* pathToTexture) {
	setTexture(pathToTexture);
}

SpriteComponent::~SpriteComponent() {
	SDL_DestroyTexture(mTexture);
}

void SpriteComponent::setTexture(const char* path) {
	mTexture = TextureManager::loadSpriteTexture(path);
	mPathToTexture = const_cast<char*>(path);
}

void SpriteComponent::init() {
	if (mSprite == nullptr) return;
	
	if (!mEntity->hasComponent<TransformComponent>()) {
		mEntity->addComponent<TransformComponent>();
	}
	
	mSprite->initTransform(&mEntity->getComponent<TransformComponent>());

	mSprite->init();
}

void SpriteComponent::update() {
	mSprite->update();

	SDL_Rect& rDestRect = mSprite->getDestRect();
	TransformComponent& rTransform = mSprite->getTransform();

	rDestRect.w = rTransform.mWidth;
	rDestRect.h = rTransform.mHeight;
	rDestRect.x = static_cast<int>(rTransform.mPosition.x);
	rDestRect.y = static_cast<int>(rTransform.mPosition.y);
}

void SpriteComponent::draw() {
	TextureManager::drawSprite(mTexture, mSprite->getSrcRect(), mSprite->getDestRect());
}

void SpriteComponent::setSprite(std::unique_ptr<Sprite> sprite) {
	if (mSprite != nullptr) {
		mSprite.reset();
	}

	mSprite = std::move(sprite);
}

std::unique_ptr<Sprite>& SpriteComponent::getSprite() {
	return mSprite;
}