#pragma once

#include "GameObject.h"

class Collectable : public GameObject
{
public:

	Collectable();
	Collectable(Transform transform);
	
	~Collectable();

	virtual void Update(float deltaTime) override;

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera);

	virtual void CollisionResponse();

protected:

	string m_image_name{ "Collectables" };

	AnimationInfo m_sprite_info{ "potato", {0, 1, 0.0f, 10, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };

};