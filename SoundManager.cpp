#include "SoundManager.h"

SoundManager::~SoundManager() {
	for (auto& sound : mSounds) {
		if (sound != nullptr) {
			Mix_FreeChunk(sound);
		}
	}

	for (auto& music : mMusic) {
		if (music != nullptr) {
			Mix_HaltMusic();
			Mix_FreeMusic(music);
		}
	}
}

void SoundManager::init() {
	Mix_AllocateChannels(mChannelsCount);

	mSounds.resize(mSoundsCount);
	mMusic.resize(mMusicCount);

	mSounds[SND_DINO_JUMP] = Mix_LoadWAV("Assets/sounds/Jump.wav");
	mSounds[SND_DINO_LAND] = Mix_LoadWAV("Assets/sounds/Land.wav");
	mSounds[SND_COLLISION] = Mix_LoadWAV("Assets/sounds/Collision.wav");

	mMusic[MORNING_MUSIC] = Mix_LoadMUS("Assets/sounds/Morning.wav");
	mMusic[NOON_MUSIC] = Mix_LoadMUS("Assets/sounds/Noon.wav");
	mMusic[NIGHT_MUSIC] = Mix_LoadMUS("Assets/sounds/Night.wav");
	mMusic[LOBBY_MUSIC] = Mix_LoadMUS("Assets/sounds/Lobby.wav");

	mInitDone = true;
}

void SoundManager::playSound(int id) {
	if (mInitDone == false) return;
	
	Mix_PlayChannel(-1, mSounds[id], 0);
}

int SoundManager::getCurrentPlayingMusic() const {
	return mCurrentPlayingMusic;
}

void SoundManager::playMusic(int id) {
	if (mInitDone == false) return;

	Mix_PlayMusic(mMusic[id], -1);

	mCurrentPlayingMusic = id;
}
