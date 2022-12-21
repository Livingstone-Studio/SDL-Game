#pragma once

#include "Player.h"

class Enemy : public Character
{
public:

	Enemy();
	Enemy(Vector2 position);
	Enemy(Transform transform);

	~Enemy();
	
	virtual void Update(float deltaTime) override;

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera) override;

	virtual void SetTarget(Character* t) { m_target = t; }

	virtual void CollisionCheck(vector<GameObject*> gameObjects) override;
	virtual void CollisionResponse() override;

protected:

	string m_image_name{ "Orc" };

	Character* m_target{ nullptr };

	Collider m_hit_area;
};