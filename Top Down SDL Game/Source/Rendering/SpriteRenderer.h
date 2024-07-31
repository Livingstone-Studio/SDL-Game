#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "../Application/AssetLoader.h"
#include "../Application/Time.h"
#include "../Application/Input.h"

class AssetLoader;
class Time;
class Input;

using namespace std;
class SpriteRenderer
{
public:

	SpriteRenderer();
	SpriteRenderer(SDL_Renderer* renderer, string imgFile);

	void SetSpriteSheet(SDL_Renderer* renderer, string imgFile);
	
	SDL_Texture* GetSpriteSheet();

	void SetSprite(int  row, int column);

	SDL_Rect GetSrcRect() { return m_srcRect; }
	SDL_Rect GetDesRect() { return m_desRect; }

	void SetDesRect(float x, float y, float xScale = 1, float yScale = 1);

	void Update();

private:

	SDL_Texture* m_spritesheet{ nullptr };

	SDL_Rect m_srcRect;
	SDL_Rect m_desRect;

	const int BASE_IMG_WIDTH{ 32 };
	const int BASE_IMG_HEIGHT{ 32 };

	float m_animTimer{ 0.0f };

	int m_currentRow{ 0 };
	int m_currentColumn{ 0 };

	int m_spritesheetWidth{ 0 };
	int m_spritesheetHeight{ 0 };

	int GetTotalSheetRows();

	int GetTotalSheetColumns();
};

