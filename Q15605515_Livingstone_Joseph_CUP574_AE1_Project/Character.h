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

	virtual void RenderDebug(SDL_Renderer* renderer, Camera camera) override;

	virtual void CollisionCheck(vector<GameObject*> gameObjects) override;	
	virtual void CollisionResponse() override;

	void TakeDamage(int health);

	bool IsDead() { return m_death; }

	bool HitCooldown();

protected:

	float m_move_speed{ 3.0f };

	int m_max_health{ 5 };
	int m_health{ 5 };

	float m_invun_time_limit{ 0.5f };
	float m_invun_timer{ 0.5f };

	bool m_attack_frame{ false };

	Vector2 m_character_collider_scale{ 0.05f,0.05f };

	bool m_dynamic_sort_order{ true };

	CharacterAnimInfo m_char_anim_info{ m_image_name,
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
		{ "attackR", {0,4,0.05f,0,false,2}, {0,4,0.05f,4,false} },
		{ "attackL", {1,4,0.05f,0,false,2}, {1,4,0.05f,4,false} },
		{ "attackTR", {2,4,0.05f,0,false,2}, {2,4,0.05f,4,false} },
		{ "attackTL", {3,4,0.05f,0,false,2}, {3,4,0.05f,4,false} },

		//Hit + Death
		{ "hitR", {7,4,0.15f,0,false}, {7,4,0.15f,4,false} },
		{ "hitL", {8,4,0.15f,0,false}, {8,4,0.15f,4,false} },
		{ "hitTR", {9,4,0.15f,0,false}, {9,4,0.15f,4,false} },
		{ "hitTL", {10,4,0.15f,0,false}, {10,4,0.15f,4,false} },
		{ "deathFR", {19,13,.15f,0,false}, {18,13,.15f,4,false} }
	};

	Collider m_attack_collider;
	Vector2 m_attack_collider_scale{ 0.11f,0.07f };

	Vector2 m_attack_collider_offset{ 0.3f,0.1f };

	Vector2 m_attempted_frame_movement;

	bool m_moving = false;
	bool m_up = false;
	bool m_right = true;

	bool m_attacking = false;
	bool m_hit = false;
	bool m_death = false;

	virtual void Animating(SDL_Renderer* renderer);

	void SetMovementDirection(Vector2 dir);

	virtual void Move(Vector2 moveVector);

	virtual void Attack() { m_attacking = true; }
	bool Interacting() { return (m_attacking || m_hit || m_death); }

};

