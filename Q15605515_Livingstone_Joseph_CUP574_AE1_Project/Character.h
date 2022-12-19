#pragma once

#include "GameObject.h"

class Character : public GameObject
{

public:

	Character();
	Character(Vector2 position);
	Character(Transform transform);

	~Character();
		
	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera) override;
	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

protected:

	virtual void Animating(SDL_Renderer* renderer);

	void SetMovementDirection(Vector2 dir);
	virtual void Move(Vector2 moveVector);
	
	void Attack() { attacking = true; }
	bool IsAttacking() { return attacking; }

	bool m_dynamic_sort_order{ true };

	float m_default_sort{ 10 };

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

	Vector2 moveDir;
	bool moving = false;
	bool up = false;
	bool right = true;
	bool attacking = false;
};

