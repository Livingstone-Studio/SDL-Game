#pragma once

#include "GameObject.h"

class Prop : public GameObject
{
public:

	Prop();
	Prop(Transform transform, string name, float sortOrder, AnimationInfo s, bool collision = false, bool dynamicSort = false, Vector2 scaleFactor = { 1,1 }, bool endTile = false);
	Prop(Transform transform, TileInfo tileInfo, bool collision = false, Vector2 scaleFactor = { 1,1 }, bool endTile = false);

	~Prop();

	virtual void Update(float deltaTime) override;

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera);

	virtual void CollisionResponse() override;

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera) override;

protected:

	bool m_end_tile{ false };

	string m_image_name{ "grass" };

	AnimationInfo m_sprite_info{ "grass", {0, 0, 0.0f, 0, false}, {0, 0, 0.0f, 0, false}, { 0, 0 } };

	AnimationInfo m_crop_info{ "grass", {0,1,0.0f,6,false} , {0,0,0.0f,-5,false}, { 0,0.5f } };
	
	Vector2 m_crop_scaling = { 4,4 };
	
};

