#pragma once

class Dino;

class DinoState {
public:
	virtual void enter(Dino& sprite) {}
	virtual void update(Dino& sprite) {}
	virtual void leave(Dino& sprite) {}
};