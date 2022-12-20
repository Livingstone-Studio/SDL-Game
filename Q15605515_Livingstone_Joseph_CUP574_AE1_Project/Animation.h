#pragma once

#include "AnimClip.h"

#include <vector>

class Camera;

class Animation
{
public:

	Animation();
	~Animation();

	void InitAnim(SDL_Renderer* renderer, string imgFile, AnimationInfo anim);

	void ChangeAnimation(SDL_Renderer* renderer, AnimationInfo animInfo);

	void Start();

	void Update();

	void RenderUpdate(SDL_Renderer* renderer, Transform transform);

	bool IsCompleted() { return completed; }

	Vector2 GetOffset();

private:

	string m_sprite_name{ "" };

	string m_anim_name{ "" };

	Vector2 m_offset{ 0,0 };

	AnimClip animClips[2];

	bool completed{ false };

};