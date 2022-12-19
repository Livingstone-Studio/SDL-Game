#pragma once

#include "GameObject.h"

class Prop : public GameObject
{
public:

	Prop();
	Prop(Transform transform, string name, float sortOrder, AnimationInfo s, bool dynamicSort = false);

	~Prop();

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera) override;

protected:

	string m_sprite_name{ "grass" };

	AnimationInfo m_sprite_info{ "grass", {0, 0, 0.0f, 0, false}, {0, 0, 0.0f, 0, false} };

};

