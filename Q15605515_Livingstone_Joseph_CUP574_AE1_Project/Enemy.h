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

	Character* m_target{ nullptr };

	Collider m_hit_area;

	CharacterAnimInfo m_charAnimInfo{ m_image_name,
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
		{ "attackTL", {3,4,0.05f,0,false}, {3,4,0.05f,4,false} },

		//Hit + Death
		{ "hitR", {8,4,0.15f,0,false}, {8,4,0.15f,4,false} },
		{ "hitL", {9,4,0.15f,0,false}, {9,4,0.15f,4,false} },
		{ "hitTR", {10,4,0.15f,0,false}, {10,4,0.15f,4,false} },
		{ "hitTL", {11,4,0.15f,0,false}, {11,4,0.15f,4,false} },
		{ "deathFR", {7,13,0.15f,0,false}, {16,13,0.15f,4,false} }
	};
};