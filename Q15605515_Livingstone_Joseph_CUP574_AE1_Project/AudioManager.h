#pragma once

#include <SDL_mixer.h>
#include <iostream>

#include "Structs.h"

using namespace std;

static class AudioManager
{
public:

	static void Initialize();

	static void Cleanup();

	static void PlayEffect(string name);

private:

	// Audio

	static Mix_Music* m_music;

	static Mix_Chunk* m_character_attack;
	static Mix_Chunk* m_character_hit;
	static Mix_Chunk* m_character_death;

	static Mix_Chunk* m_character_walk;

	static Mix_Chunk* m_slime_walk;
	static Mix_Chunk* m_slime_land;


};