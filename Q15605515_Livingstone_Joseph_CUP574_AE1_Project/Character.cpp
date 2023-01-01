#include "Character.h"

#include "Game.h"

Character::Character()
	: m_attack_collider(false, true, { 0.3f,0.1f })
{
	m_collider_scale = m_character_collider_scale;

	m_attack_collider_offset = m_attack_collider.GetCollisionOffset();
}

Character::Character(Vector2 position)
	: m_attack_collider(false, true, { 0.3f,0.1f })
{
	m_collider_scale = m_character_collider_scale;
	m_transform.position = position;

	m_attack_collider_offset = m_attack_collider.GetCollisionOffset();
}

Character::Character(Transform transform)
	: m_attack_collider(false, true, { 0.3f,0.1f })
{
	m_collider_scale = m_character_collider_scale;
	m_transform = transform;

	m_attack_collider_offset = m_attack_collider.GetCollisionOffset();
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
	if (m_frame_collided.size() > 0)
	{
		CollisionResponse();
	}

	m_invun_timer += Time::GetDeltaTime();

	if (!m_death) Move(m_attempted_frame_movement);

	GameObject::Update(deltaTime);

	m_attack_frame = false;
}

void Character::Move(Vector2 moveVector)
{
	m_transform.position += moveVector;
}

void Character::Attack()
{
	if (m_attacking == false) AudioManager::PlayEffect("charAttack");
	m_attacking = true;
}

void Character::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_char_anim_info.idleR);

	GameObject::RenderStart(renderer, camera);
}

void Character::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	Animating(renderer);

	GameObject::RenderUpdate(renderer, camera);
}

void Character::RenderDebug(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_collider.GetActive())
	{
		m_collider_debug.SetAnimation({ 0, 1, 0.0f, 0, false });

		Vector2 offset = m_collider.GetCollisionOffset();

		if (m_collider.GetActive()) m_collider_debug.RenderUpdate(renderer, camera.ConvertedToScreenSpace({ m_transform.position + m_attempted_frame_movement + offset, m_transform.scale * m_collider_scale * m_debug_box_scale }));

		offset = m_attack_collider.GetCollisionOffset();

		m_collider_debug.RenderUpdate(renderer, camera.ConvertedToScreenSpace({ m_transform.position + m_attempted_frame_movement + offset, m_transform.scale * m_attack_collider_scale * m_debug_box_scale }));


	}
}

void Character::CollisionCheck(vector<GameObject*> gameObjects)
{
	m_frame_collided.clear();

	if (m_death) return;

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
	}
	
	m_attack_collider.SetActive(false);
	m_attack_frame = false;
}

void Character::CollisionResponse()
{
	for (int i = 0; i < m_frame_collided.size(); i++)
	{
		if (!m_frame_collided[i].info.trigger && !m_frame_collided[i].gameObject->GetCollider().IsTrigger())
		{
			//cout << "H: " << m_frame_collided[i].info.hor << ",V: " << m_frame_collided[i].info.vert << endl;

			Character* character = dynamic_cast<Character*>(m_frame_collided[i].gameObject);

			if (character == nullptr)
			{
				m_attempted_frame_movement = { 0,0 };
			}

		}
		else 
		{
			if (m_frame_collided[i].gameObject != nullptr && m_frame_collided[i].gameObject != this)
			{
				Character* character = dynamic_cast<Character*>(m_frame_collided[i].gameObject);

				if (character != nullptr) 
				{
					// Take Damage
					character->TakeDamage(1);
				}
			}
		}
	}
}

void Character::TakeDamage(int health)
{
	if (m_hit || m_death || !HitCooldown()) return;

	m_health -= health;
		
	if (m_health <= 0) 
	{
		m_death = true;
		AudioManager::PlayEffect("charDeath");
		m_health = 0;
	}
	else 
	{
		m_hit = true;
		AudioManager::PlayEffect("charHit");
		m_invun_timer = 0.0f;
	}
}

bool Character::HitCooldown()
{
	if (m_invun_timer > m_invun_time_limit) return true;

	return false;
}

void Character::Animating(SDL_Renderer* renderer)
{
	if (m_death) 
	{
		m_gfx.ChangeAnimation(renderer, m_char_anim_info.death);

		if (m_gfx.IsCompleted()) Delete();

		return;
	}

	if (m_attempted_frame_movement.x != 0 || m_attempted_frame_movement.y != 0) m_moving = true;
	else m_moving = false;

	if (m_attacking) m_attacking = !m_gfx.IsCompleted();
	if (m_hit) m_hit = !m_gfx.IsCompleted();

	if (!Interacting())
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
			

			if ((m_gfx.OneIsTriggered() && !m_gfx.OneIsAlreadyTriggered()) || (m_gfx.TwoIsTriggered() && !m_gfx.TwoIsAlreadyTriggered()))
			{
				AudioManager::PlayEffect("charWalk");
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
		else if (m_attacking) 
		{
			if (m_right && !m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.attackR);
			else if (!m_right && !m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.attackL);
			else if (m_right && m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.attackTR);
			else if (!m_right && m_up) m_gfx.ChangeAnimation(renderer, m_char_anim_info.attackTL);
		}
		
	}

	if (m_right && !m_up) m_attack_collider.SetCollisionOffset({m_attack_collider_offset.x, m_attack_collider_offset.y * - 1});
	else if (!m_right && !m_up) m_attack_collider.SetCollisionOffset({ m_attack_collider_offset.x * -1, m_attack_collider_offset.y * -1 });
	else if (m_right && m_up) m_attack_collider.SetCollisionOffset({ m_attack_collider_offset.x, m_attack_collider_offset.y });
	else if (!m_right && m_up) m_attack_collider.SetCollisionOffset({ m_attack_collider_offset.x * -1, m_attack_collider_offset.y});
}

void Character::SetMovementDirection(Vector2 dir)
{
	if (!Interacting()) m_attempted_frame_movement = dir.Normalized() * m_move_speed * Time::GetDeltaTime();
	else m_attempted_frame_movement = { 0,0 };
}