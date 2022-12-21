#pragma once

#include "GameObject.h"

class Prop : public GameObject
{
public:

	Prop();
	Prop(Transform transform, string name, float sortOrder, AnimationInfo s, bool collision = false, bool dynamicSort = false, Vector2 scaleFactor = { 1,1 });
	Prop(Transform transform, TileInfo tileInfo, bool collision = false, Vector2 scaleFactor = { 1,1 });

	~Prop();

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera) override;

protected:

	string m_image_name{ "grass" };

	AnimationInfo m_sprite_info{ "grass", {0, 0, 0.0f, 0, false}, {0, 0, 0.0f, 0, false}, { 0, 0 } };

};

