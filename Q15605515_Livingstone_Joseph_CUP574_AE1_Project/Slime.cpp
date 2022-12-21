#include "Slime.h"

Slime::Slime()
{
	m_move_speed = 1.0f;
	m_char_anim_info = m_charAnimInfo;
	m_attack_collider = { true, true};
	m_attack_collider_scale = { 0.05f,0.05f };
	m_attack_collider_offset = { 0,0 };
}

Slime::Slime(Vector2 position)
{
	m_move_speed = 1.0f;
	m_char_anim_info = m_charAnimInfo;
	m_transform = { position };
	m_attack_collider = { true, true};
	m_attack_collider_scale = { 0.05f,0.05f };
	m_attack_collider_offset = { 0,0 };
}

Slime::Slime(Transform transform)
{
	m_move_speed = 1.0f;
	m_char_anim_info = m_charAnimInfo;
	m_transform = transform;
	m_attack_collider = { true, true };
	m_attack_collider_scale = { 0.05f,0.05f };
	m_attack_collider_offset = { 0,0 };
}

void Slime::Attack()
{
	m_attacking = true;
}

void Slime::Update(float deltaTime)
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

	SetMovementDirection(moveVector);

	Character::Update(deltaTime);
}

void Slime::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_charAnimInfo.idleR);

	GameObject::RenderStart(renderer, camera);
}

void Slime::Animating(SDL_Renderer* renderer)
{
	if (m_death)
	{
		m_gfx.ChangeAnimation(renderer, m_char_anim_info.death);

		if (m_gfx.IsCompleted()) Delete();

		return;
	}

	if (m_attempted_frame_movement.x != 0 || m_attempted_frame_movement.y != 0) m_moving = true;
	else m_moving = false;

	if (m_hit) m_hit = !m_gfx.IsCompleted();


	if (!m_hit)
	{
		if (m_moving)
		{
			if (m_attempted_frame_movement.x > 0.0f) {

				if (m_up)
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveTR);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveR);
				}

				m_right = true;
			}
			else if (m_attempted_frame_movement.x < 0.0f) {

				if (m_up)
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveTL);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveL);
				}

				m_right = false;
			}

			if (m_attempted_frame_movement.y < 0.0f) {

				if (m_right)
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveR);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveL);
				}

				m_up = false;
			}
			else if (m_attempted_frame_movement.y > 0.0f) {

				if (m_right)
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveTR);
				}
				else
				{
					m_gfx.ChangeAnimation(renderer, m_char_anim_info.moveTL);
				}

				m_up = true;
			}
		}
		else
		{
			if (m_right && !m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.idleR);
			else if (!m_right && !m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.idleL);
			else if (m_right && m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.idleTR);
			else if (!m_right && m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.idleTL);
		}
	}
	else
	{
		if (m_hit)
		{
			if (m_right && !m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.hitR);
			else if (!m_right && !m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.hitL);
			else if (m_right && m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.hitTR);
			else if (!m_right && m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.hitTL);
		}
	}

	if (m_attacking)
	{
		m_attack_frame = true;
	}
}

void Slime::SetMovementDirection(Vector2 dir)
{
	if (m_target != nullptr) 
	{
		if (!m_hit && (m_target->GetTransform().position - m_transform.position).Magnitude() > m_range) m_attempted_frame_movement = dir.Normalized() * m_move_speed * Time::GetDeltaTime();
	}
	else m_attempted_frame_movement = { 0,0 };
}

void Slime::CollisionCheck(vector<GameObject*> gameObjects)
{
	m_frame_collided.clear();

	if (m_death) return;

	m_hit_area = m_attack_collider;
	m_hit_area.SetActive(true);

	m_attack_frame = true;

	if (m_attack_frame) m_attack_collider.SetActive(true);

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
