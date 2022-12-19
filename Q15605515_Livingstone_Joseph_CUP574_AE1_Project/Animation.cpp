#include "Animation.h"

Animation::Animation()
	: animClips()
{
}

Animation::~Animation()
{
}

void Animation::InitAnim(SDL_Renderer* renderer, string imgFile, AnimationInfo anim)
{
	m_sprite_name = imgFile;
	animClips[0].Initialize(renderer, imgFile, anim.actionAnimClip);
	animClips[1].Initialize(renderer, imgFile, anim.actionAnimShadow);
}

void Animation::ChangeAnimation(SDL_Renderer* renderer, AnimationInfo animInfo)
{
	if (m_anim_name != animInfo.name) 
	{
		if (animClips[0].IsInitialized() && animClips[1].IsInitialized())
		{
			m_anim_name = animInfo.name;
			animClips[0].SetAnimation(animInfo.actionAnimClip);
			animClips[1].SetAnimation(animInfo.actionAnimShadow);
		}
		else 
		{
			InitAnim(renderer, m_sprite_name, animInfo);
		}
	}
}

void Animation::Start()
{
}

void Animation::Update()
{
	for (int i = 0; i < 2; i++)
	{
		bool clipComp = animClips[1 - i].Update();

		if (i == 0) completed = clipComp;
	}
}

void Animation::RenderUpdate(SDL_Renderer* renderer, Transform transform)
{
	for (int i = 0; i < 2; i++)
	{
		animClips[1 - i].RenderUpdate(renderer, transform);
	}
}
