#pragma once

#include "Character.h"

class Enemy : public Character
{
public:

	Enemy();
	Enemy(Vector2 position);
	Enemy(Transform transform);

	~Enemy();
	
	virtual void Update(float deltaTime) override;

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera) override;

	virtual void SetTarget(GameObject* t) { m_target = t; }

protected:

	GameObject* m_target{ nullptr };

	float m_attackRange{ .5f };

	CharacterAnimInfo m_charAnimInfo{ m_sprite_name,
		//Idle
		{ "idleR", {20,1,0,0,true}, {20,1,0,4,true}},
		{ "idleL", {21,1,0,0,true}, {21,1,0,4,true} },
		{ "idleTR", {22,1,0,0,true}, {22,1,0,4,true} },
		{ "idleTL", {23,1,0,0,true}, {23,1,0,4,true} },

		//Move
		{ "moveR", {20,4,0.1f,0,true}, {20,4,0.1f,4,true} },
		{ "moveL", {21,4,0.1f,0,true}, {21,4,0.1f,4,true} },
		{ "moveTR", {22,4,0.1f,0,true}, {22,4,0.1f,4,true} },
		{ "moveTL", {23,4,0.1f,0,true}, {23,4,0.1f,4,true} },

		//Attack
		{ "attackR", {0,4,0.05f,0,false}, {0,4,0.05f,4,false} },
		{ "attackL", {1,4,0.05f,0,false}, {1,4,0.05f,4,false} },
		{ "attackTR", {2,4,0.05f,0,false}, {2,4,0.05f,4,false} },
		{ "attackTL", {3,4,0.05f,0,false}, {3,4,0.05f,4,false} }
	};
};