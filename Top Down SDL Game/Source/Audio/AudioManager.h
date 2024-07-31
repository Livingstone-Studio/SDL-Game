#pragma once

#include <SDL_mixer.h>
#include <iostream>

#include "../Application/Structs.h"

using namespace std;

static class AudioManager
{
public:

	static void Initialize();

	static void Cleanup();

	static void PlayEffect(string name);

	static void ToggleEffects();

	static void ToggleMusic();

private:

	// Audio

	static bool m_effects_active;

	static bool m_music_active;

	static Mix_Music* m_music;

	static Mix_Chunk* m_character_attack;
	static Mix_Chunk* m_character_hit;
	static Mix_Chunk* m_character_death;

	static Mix_Chunk* m_character_walk;

	static Mix_Chunk* m_slime_walk;
	static Mix_Chunk* m_slime_land;

	static Mix_Chunk* m_pickup_collectable;

	static Mix_Chunk* m_button_hover_start;
	static Mix_Chunk* m_button_hover_stop;
	static Mix_Chunk* m_button_press;

};