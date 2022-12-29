#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Input.h"
#include "Time.h"
#include "Maths.h"
#include "AssetLoader.h"
#include "LevelHandler.h"

#include "Camera.h"

#include "GameObject.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Orc.h"
#include "Slime.h"
#include "Collectable.h"
#include "AudioManager.h"

#include <vector>

using namespace std;

class Camera;

class GameObject;
class Character;
class Player;
class Enemy;

enum GameState {
	SMainMenu, Gameplay
};

class Game
{
public:

	Game();

	void Execute();

	void GameExecute();

	static SDL_Renderer* GetRenderer() { return m_renderer; }

	static void ToggleDebug() {	m_debug = !m_debug;	}

	static void Play();
	static void ReturnToMenu();

	static void Quit() { m_main_menu = false; }

	static bool DebugMode() { return m_debug; }

private:

	static GameState m_game_state;

	static bool m_main_menu;

	static bool m_menu_first_frame;

	static bool m_run;
	static bool m_debug;

	static SDL_Window* m_window;
	static SDL_Renderer* m_renderer;

	bool m_fullscreen{ false };

	Camera m_camera;


	Player* m_player_cast;
	vector<GameObject*> m_gameobjects;

	const char* WINDOW_NAME = "Gobbie the Gobbo Farmer";
	 int DEFAULT_WINDOW_WIDTH = 960;
	const int DEFAULT_WINDOW_HEIGHT = 590;

	void Setup();

	void AppLoop();

	void GameSetup();

	void FrameInit();

	void GameLoop();

	void FrameCleanup();

	void InputHandler();

	void EventHandler();

	void RendererHandler();

	void GameClose();

	void Close();

	// DEBUG
	void SpawnOrc();
	void SpawnSlime();
	void KillEnemy();
};