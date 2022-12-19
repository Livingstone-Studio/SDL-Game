#pragma once

#include "Sprite.h"

class AnimClip
{

public:

	AnimClip();

	void Initialize(SDL_Renderer* renderer, string imgFile, AnimClipInfo anim);
		
	void SetAnimation(AnimClipInfo anim);

	void DebugCurrentSpriteInfo();

	SDL_Texture* GetSprite();

	void SetAnimationSprite(int  row, int column);

	SDL_Rect GetSrcRect() { return m_spritesheet.GetSrcRect(); }
	SDL_Rect GetDesRect() { return m_spritesheet.GetDesRect(); }

	void SetDesRect(float x, float y, float xScale = 1, float yScale = 1);
	void SetDesRect(Transform transform);

	bool Update();

	void RenderUpdate(SDL_Renderer* renderer, Transform transform);

	bool IsInitialized() { return m_initialized; }

private:

	bool m_initialized{ false };

	Sprite m_spritesheet;

	float m_animTimeBetween{ 1.0 };
	float m_animTimer{ 0.0f };

	int m_row{ 0 };
	int m_spriteCount{ 0 };
	int m_startSpriteIndex{ 0 };
	int m_currentSpriteIndex{ 0 };
	bool m_looping{ true };

};