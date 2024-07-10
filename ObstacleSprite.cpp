#include "Sprites.h"
#include "Game.h"

void DyingTree1::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Sh*t! caught in the Dying Trees!\nWriggle out for your next run?");

	setSrcRect(0, 0, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 101, 263, 136, 137);
}

void DyingTree1::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 49, rTransform.mPosition.y + 4, 100, 136);
	
	}
}



void DyingTree2::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Sh*t! caught in the Dying Trees!\nWriggle out for your next run?");
	

	setSrcRect(32, 0, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 101, 263, 136, 137);
}

void DyingTree2::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 36, rTransform.mPosition.y + 46, 40, 87);
	
	}
}



void Bucket::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Danmit! You've kicked The Bucket\nDid I mention you have nine (ahem) lives?");

	setSrcRect(64, 0, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 101, Game::mSCREEN_HEIGHT - 240, 153, 160);
}

void Bucket::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 25, rTransform.mPosition.y + 29, 128, 100);
	
	}
}



void TreeStump::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Oof! crashed right into a Tree Stump!\nWatch your path, Rex!");

	setSrcRect(0, 32, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 101, 263, 136, 137);
}

void TreeStump::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 61, rTransform.mPosition.y + 81, 81, 51);
	
	}
}



void Stalker::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Hehe, the one-eyed Stalker...\nLook away next time, okay?");

	if (Game::mSpeedToggled) {
		setAnimation(1, 2, 150);
	}
	else {
		setAnimation(1, 2, 200);
	}

	setSrcRect(32, 32, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 101, 263, 136, 137);
}

void Stalker::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 54, rTransform.mPosition.y + 4, 82, 136);
	
	}

	rSrcRect.x = 32 + (rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount()));
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}



void Brute::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Ouch, crushed by the merciless Brute!\nOh well, you're not THAT hurt, go again?");

	if (Game::mSpeedToggled) {
		setAnimation(2, 2, 150);
	}
	else {
		setAnimation(2, 2, 200);
	}

	setSrcRect(0, 64, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 101, 247, 153, 153);
}

void Brute::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 25, rTransform.mPosition.y + 28, 125, 130);
	
	}

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}


void StalkerPup::init() {
	auto upMidDown = std::rand() % 15;

	if (Game::mSpeedToggled) {
		setAnimation(3, 2, 150);
	}
	else {
		setAnimation(3, 2, 200);
	}

	setSrcRect(0, 96, 32, 32);
	
	getCollider().resize(1);
	getCollider().setCollisionTag("Yikes, Stalker Pups...\nNothing to see or say here, Rex, run again?");

	if (upMidDown <= 7) {
		setTransform(Game::mSCREEN_WIDTH + 101, 220, 103, 105);
	}
	else if (upMidDown <= 15) {
		setTransform(Game::mSCREEN_WIDTH + 101, Game::mSCREEN_HEIGHT - 200, 103, 105);
	}
}

void StalkerPup::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 12, rTransform.mPosition.y, 100, 75);
	
	}

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}



void Gale::init() {
	auto upMidDown = std::rand() % 15;

	if (Game::mSpeedToggled) {
		setAnimation(4, 2, 150);
	}
	else {
		setAnimation(4, 2, 200);
	}

	setSrcRect(0, 128, 32, 32);

	getCollider().resize(1);
	getCollider().setCollisionTag("Whoaa, you let the Night Gale sweep you away?\nHold on tight next run!");

	if (upMidDown <= 7) {
		setTransform(Game::mSCREEN_WIDTH + 101, 220, 103, 105);
	}
	else if (upMidDown <= 15) {
		setTransform(Game::mSCREEN_WIDTH + 101, Game::mSCREEN_HEIGHT - 200, 103, 105);
	}
}

void Gale::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mVelocity.x < 0) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 12, rTransform.mPosition.y, 100, 75);
	
	}

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}