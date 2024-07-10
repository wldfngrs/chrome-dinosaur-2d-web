#pragma once

#include "SDL_mixer.h"

#include <vector>
#include <string>

enum {
	SND_DINO_JUMP,
	SND_DINO_LAND,
	SND_COLLISION,
};

enum {
	MORNING_MUSIC,
	NOON_MUSIC,
	NIGHT_MUSIC,
	LOBBY_MUSIC
};

class SoundManager {
	const int mChannelsCount = 8;
	const int mSoundsCount = 3;
	const int mMusicCount = 4;

	int mCurrentPlayingMusic = 0;

	bool mInitDone = false;

	std::vector<Mix_Chunk*> mSounds;
	std::vector<Mix_Music*> mMusic;

public:
	~SoundManager();

	void init();
	void playSound(int id);
	void playMusic(int id);

	int getCurrentPlayingMusic() const;
};