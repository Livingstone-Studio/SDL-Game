#pragma once

#include "GameObject.h"
class Collectable : public GameObject
{
public:

	Collectable();
	Collectable(Transform transform, bool isKey = false);
	
	~Collectable();

	virtual void Update(float deltaTime) override;

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera);

	virtual void CollisionResponse();

	virtual int GetScore() { return m_score; }

	virtual bool IsKey() { return m_key; }

protected:

	bool m_key{ false };

	int m_score{ 10 };

	string m_image_name{ "Collectables" };

	AnimationInfo m_sprite_info{ "potato", {2, 1, 0.0f, 14, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };
	AnimationInfo m_gfx_info{ "potato", {0, 1, 0.0f, 10, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };

};