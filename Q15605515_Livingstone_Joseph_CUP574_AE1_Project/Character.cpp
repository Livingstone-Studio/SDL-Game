#include "Character.h"

Character::Character()
{
}

Character::Character(Vector2 position)
{
	m_transform.position = position;

}

Character::Character(Transform transform)
{
	m_transform = transform;
}

Character::~Character()
{
}

void Character::Start()
{
	GameObject::Start();
}

void Character::Update(float deltaTime)
{
	Move({ moveDir.x * deltaTime * 3, moveDir.y * deltaTime * 3 });

	GameObject::Update(deltaTime);
}

void Character::Move(Vector2 moveVector)
{
	m_transform.position += moveVector;

}

void Character::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_sprite_name, m_charAnimInfo.idleR);

	GameObject::RenderStart(renderer, camera);
}

void Character::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	Animating(renderer);

	GameObject::RenderUpdate(renderer, camera);
}

void Character::Animating(SDL_Renderer* renderer)
{
	if (moveDir.x != 0 || moveDir.y != 0) moving = true;
	else moving = false;

	if (attacking) attacking = !m_gfx.IsCompleted();

	if (!attacking)
	{
		if (moving)
		{
			if (moveDir.x > 0.0f) {

				if (up)
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveTR);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveR);
				}

				right = true;
			}
			else if (moveDir.x < 0.0f) {

				if (up)
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveTL);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveL);
				}

				right = false;
			}

			if (moveDir.y < 0.0f) {

				if (right)
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveR);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveL);
				}

				up = false;
			}
			else if (moveDir.y > 0.0f) {

				if (right)
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveTR);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_charAnimInfo.moveTL);
				}

				up = true;
			}
		}
		else
		{
			if (right && !up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.idleR);
			else if (!right && !up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.idleL);
			else if (right && up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.idleTR);
			else if (!right && up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.idleTL);
		}
	}
	else
	{
		if (right && !up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.attackR);
		else if (!right && !up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.attackL);
		else if (right && up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.attackTR);
		else if (!right && up) m_gfx.ChangeAnimation(renderer, m_charAnimInfo.attackTL);
	}

}

void Character::SetMovementDirection(Vector2 dir)
{
	if (!IsAttacking()) moveDir = dir;
	else moveDir = { 0,0 };
}
