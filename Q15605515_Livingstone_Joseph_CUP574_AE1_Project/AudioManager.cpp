#include "AudioManager.h"

Mix_Music* AudioManager::m_music{ nullptr };

Mix_Chunk* AudioManager::m_character_attack{ nullptr };
Mix_Chunk* AudioManager::m_character_hit{ nullptr };
Mix_Chunk* AudioManager::m_character_death{ nullptr };

Mix_Chunk* AudioManager::m_character_walk{ nullptr };

Mix_Chunk* AudioManager::m_slime_walk{ nullptr };
Mix_Chunk* AudioManager::m_slime_land{ nullptr };

void AudioManager::Initialize()
{
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) 
	{
		cout << "Failed to open Audio device. Error: " << Mix_GetError() << endl;
	}

	m_music = Mix_LoadMUS("Assets/Audio/Abstraction - Ludum Dare 38 Loops/Ludum Dare 38 - Track 9.wav");

	Mix_VolumeMusic(32);

	m_character_attack = Mix_LoadWAV("Assets/Audio/CharacterAttack.wav");
	m_character_hit = Mix_LoadWAV("Assets/Audio/CharacterHit.wav");
	m_character_death = Mix_LoadWAV("Assets/Audio/CharacterDeath.wav");

	m_character_walk = Mix_LoadWAV("Assets/Audio/CharacterWalk.wav");

	m_slime_walk = Mix_LoadWAV("Assets/Audio/SlimeWalk.wav");
	m_slime_land = Mix_LoadWAV("Assets/Audio/SlimeLand.wav");

	if (m_music != nullptr) Mix_PlayMusic(m_music, -1);
	else cout << "Can't find music." << endl;
}

void AudioManager::Cleanup()
{

	Mix_FreeMusic(m_music);

	Mix_FreeChunk(m_character_attack);
	Mix_FreeChunk(m_character_hit);
	Mix_FreeChunk(m_character_death);
	Mix_FreeChunk(m_character_walk);
	Mix_FreeChunk(m_slime_walk);
	Mix_FreeChunk(m_slime_land);

	Mix_CloseAudio();
	Mix_Quit();
}

void AudioManager::PlayEffect(string name)
{
	Mix_Chunk* track = nullptr;

	// Character Attacking Sounds
	if (name == "charAttack" && m_character_attack != nullptr) track = m_character_attack;
	else if (name == "charHit" && m_character_hit != nullptr) track = m_character_hit;
	else if (name == "charDeath" && m_character_death != nullptr) track = m_character_death;

	// Character Footsteps
	else if (name == "charWalk" && m_character_walk != nullptr) track = m_character_walk;


	// Slime Footsteps
	else if (name == "slimeWalk" && m_slime_walk != nullptr) track = m_slime_walk;
	else if (name == "slimeLand" && m_slime_land != nullptr) track = m_slime_land;

	if (track != nullptr)
	{
		Mix_VolumeChunk(track, 50);
		Mix_PlayChannel(-1, track, 0);
	}
	else cout << "Can't find sound effect." << endl;
}