#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Vector2 position)
{
	m_transform = { position };
}

Enemy::Enemy(Transform transform)
{
	m_transform = transform;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{	
	Vector2 moveDir;

	if (m_target != nullptr) 
	{
		moveDir = m_target->GetTransform().position - m_transform.position;

		if (moveDir.Magnitude() < m_attackRange)
		{
			Attack();
		}
	}
	else {
		cout << "Invalid Target" << endl;
	}
	
	SetMovementDirection(moveDir.Normalized());
	
	Character::Update(deltaTime);
}

void Enemy::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_sprite_name, m_charAnimInfo.idleR);

	GameObject::RenderStart(renderer, camera);
}
