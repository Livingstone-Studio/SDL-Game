#include "Enemy.h"
#include "../Application/Game.h"


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
	Vector2 moveVector;

	if (m_target != nullptr) 
	{
		if (InRange()) 
		{
			moveVector = m_target->GetTransform().position - m_transform.position;

			if (m_target->IsDead() || Game::GetCanvasState() == VictoryScreen)
			{
				m_target = nullptr;
			}
		}
	}

	SetMovementDirection(moveVector);
	
	Character::Update(deltaTime);

}

void Enemy::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_char_anim_info.idleR);

	GameObject::RenderStart(renderer, camera);
}

void Enemy::CollisionCheck(vector<GameObject*> gameObjects)
{
	m_frame_collided.clear();

	if (m_death) return;

	m_hit_area = m_attack_collider;
	m_hit_area.SetActive(true);

	if (m_attacking && !m_gfx.OneIsAlreadyTriggered())
{
	m_attack_frame = m_gfx.OneIsTriggered();
}

	if (m_attack_frame) m_attack_collider.SetActive(true);

	if (!m_collider.GetActive())
{
	return;
}

	for (int i = 0; i < gameObjects.size(); i++)
{
		Vector2 distance = gameObjects[i]->GetTransform().position - m_transform.position;

		if ((distance.Absolute()).Magnitude() < 2.0f)
		{
			if (gameObjects[i] != this && gameObjects[i]->GetCollider().GetActive() && m_collider.GetActive())
			{
				Collided c = { gameObjects[i], m_collider.CollisionCheck(
					m_collider.IsTrigger(),
				  {
					m_transform.position.x + m_attempted_frame_movement.x,
					m_transform.position.y + m_attempted_frame_movement.y,
					m_transform.scale.x * m_collider_scale.x,
					m_transform.scale.y * m_collider_scale.y
				  },
				  { gameObjects[i]->GetTransform().position.x,
					gameObjects[i]->GetTransform().position.y,
					gameObjects[i]->GetTransform().scale.x * gameObjects[i]->GetColliderScale().x,
					gameObjects[i]->GetTransform().scale.y * gameObjects[i]->GetColliderScale().y
				  })
				};

				if (c.info.collided)
				{
					m_frame_collided.push_back(c);
				}
			}

			if (gameObjects[i] != this && gameObjects[i]->GetCollider().GetActive() && m_attack_collider.GetActive())
			{
				Collided c = { gameObjects[i], m_collider.CollisionCheck(
					m_attack_collider.IsTrigger(),
				  {
					m_transform.position.x + m_attempted_frame_movement.x + m_attack_collider.GetCollisionOffset().x,
					m_transform.position.y + m_attempted_frame_movement.y + m_attack_collider.GetCollisionOffset().y,
					m_transform.scale.x * m_attack_collider_scale.x,
					m_transform.scale.y * m_attack_collider_scale.y
				  },
				  { gameObjects[i]->GetTransform().position.x,
					gameObjects[i]->GetTransform().position.y,
					gameObjects[i]->GetTransform().scale.x * gameObjects[i]->GetColliderScale().x,
					gameObjects[i]->GetTransform().scale.y * gameObjects[i]->GetColliderScale().y
				  })
				};

				if (c.info.collided)
				{
					m_frame_collided.push_back(c);
				}
			}

			if (gameObjects[i] != this && gameObjects[i]->GetCollider().GetActive() && m_hit_area.GetActive())
			{
				Collided c = { gameObjects[i], m_collider.CollisionCheck(
					m_hit_area.IsTrigger(),
				  {
					m_transform.position.x + m_attempted_frame_movement.x + m_hit_area.GetCollisionOffset().x,
					m_transform.position.y + m_attempted_frame_movement.y + m_hit_area.GetCollisionOffset().y,
					m_transform.scale.x * m_attack_collider_scale.x,
					m_transform.scale.y * m_attack_collider_scale.y
				  },
				  { gameObjects[i]->GetTransform().position.x,
					gameObjects[i]->GetTransform().position.y,
					gameObjects[i]->GetTransform().scale.x * gameObjects[i]->GetColliderScale().x,
					gameObjects[i]->GetTransform().scale.y * gameObjects[i]->GetColliderScale().y
				  })
				};

				if (c.info.collided)
				{
					m_frame_collided.push_back(c);
				}
			}
		}
}

m_attack_collider.SetActive(false);
}

void Enemy::CollisionResponse()
{
	for (int i = 0; i < m_frame_collided.size(); i++)
	{
		if (!m_frame_collided[i].info.trigger && !m_frame_collided[i].gameObject->GetCollider().IsTrigger())
		{
			Character* character = dynamic_cast<Character*>(m_frame_collided[i].gameObject);
			Collectable* collectable = dynamic_cast<Collectable*>(m_frame_collided[i].gameObject);

			if (character == nullptr && collectable == nullptr)
			{
				Vector2 potiential_move = (m_transform.position + m_attempted_frame_movement);

				if ((((m_frame_collided[i].info.c2_transform.position - potiential_move).Absolute()).Magnitude())
					< 
					(((m_frame_collided[i].info.c2_transform.position - m_transform.position).Absolute()).Magnitude()))
				{
					m_attempted_frame_movement = { 0,0 };
				}
			}
		}
		else
		{
			if (m_frame_collided[i].gameObject != nullptr && m_frame_collided[i].gameObject != this)
			{
				Character* character = dynamic_cast<Character*>(m_frame_collided[i].gameObject);

				if (character != nullptr && character == m_target && m_attack_frame)
				{
					character->TakeDamage(1);
					m_attack_frame = false;
				}
				else if (character != nullptr && character == m_target && !m_attack_frame) 
				{
					Attack();
				}
			}
		}
	}
}

bool Enemy::InRange()
{
	Vector2 targetpos = m_target->GetTransform().position;

	if (!m_chasing)
	{
		m_chasing = ((targetpos - m_transform.position).Magnitude() < 6);
	}

	if (m_chasing) 
	{
		return true;
	}

	return false;
}
