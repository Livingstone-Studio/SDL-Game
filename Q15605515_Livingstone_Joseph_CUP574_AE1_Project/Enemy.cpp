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
	Vector2 moveVector;

	if (m_target != nullptr) 
	{
		moveVector = m_target->GetTransform().position - m_transform.position;

		if (m_target->IsDead()) 
		{
			m_target = nullptr;
		}
	}
	else {
	}

	SetMovementDirection(moveVector);
	
	Character::Update(deltaTime);

}

void Enemy::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_charAnimInfo.idleR);

	GameObject::RenderStart(renderer, camera);
}

void Enemy::CollisionCheck(vector<GameObject*> gameObjects)
{
	m_hit_area = m_attack_collider;
	m_hit_area.SetActive(true);

	if (m_attacking && !m_gfx.IsAlreadyTriggered())
	{
		m_attack_frame = m_gfx.IsTriggered();
	}

	if (m_attack_frame) m_attack_collider.SetActive(true);

	m_frame_collided.clear();

	if (!m_collider.GetActive())
	{
		return;
	}

	for (int i = 0; i < gameObjects.size(); i++)
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

	m_attack_collider.SetActive(false);
}

void Enemy::CollisionResponse()
{
	for (int i = 0; i < m_frame_collided.size(); i++)
	{
		if (!m_frame_collided[i].info.trigger)
		{
			//cout << "H: " << m_frame_collided[i].info.hor << ",V: " << m_frame_collided[i].info.vert << endl;

			Character* character = dynamic_cast<Character*>(m_frame_collided[i].gameObject);

			if (character == nullptr) 
			{
				m_attempted_frame_movement = { 0,0 };
			}

			//Vector2 pos1 = m_frame_collided[i].info.c1_transform.position;
			//Vector2 pos2 = m_frame_collided[i].info.c2_transform.position;

			//Vector2 dir = pos2 - pos1;

			//if (dir.x > 0 || dir.x < 0) moveDir.x = 0;
			//if (dir.y > 0 || dir.y < 0) moveDir.y = 0;

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
