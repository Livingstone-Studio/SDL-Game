#pragma once

#include "AnimClip.h"

#include <vector>

class Animation
{
public:

	Animation();

	void InitAnim(SDL_Renderer* renderer, string imgFile, AnimationInfo anim);

	~Animation();

	void ChangeAnimation(SDL_Renderer* renderer, AnimationInfo animInfo);

	void Start();

	void Update();

	void RenderUpdate(SDL_Renderer* renderer, Transform transform);

	bool IsCompleted() { return completed; }

private:

	string m_sprite_name{ "" };

	string m_anim_name{ "" };

	AnimClip animClips[2];

	bool completed{ false };

};