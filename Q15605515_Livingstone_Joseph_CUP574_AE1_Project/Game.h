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

#include <vector>

using namespace std;

class Camera;

class GameObject;
class Character;
class Player;
class Enemy;

class Game
{
public:

	Game();

	int Execute();

	static void Quit();

	static SDL_Renderer* GetRenderer() { return m_renderer; }

private:

	static bool m_run;

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

	void FrameInit();

	void GameLoop();

	void FrameCleanup();

	void InputHandler();

	void EventHandler();

	void RendererHandler();

	void Close();

	// TEMP
	void SpawnEnemy();
	void KillEnemy();
};