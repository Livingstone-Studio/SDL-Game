#include "Player.h"

Player::Player()
{
    m_move_speed = 5.0f;
}

Player::Player(Vector2 position)
{
	m_transform.position = position;
    m_move_speed = 5.0f;

}

Player::Player(Transform transform)
{
	m_transform = transform;
    m_move_speed = 5.0f;
}

Player::~Player()
{
}

void Player::RenderStart(SDL_Renderer* renderer, Camera camera)
{
    m_gfx.InitAnim(renderer, m_image_name, m_char_anim_info.idleR);

    GameObject::RenderStart(renderer, camera);
}

void Player::InputUpdate(float deltaTime)
{
    if (m_death) return;
    Vector2 moveVector;

    if (Input::GetKey(SDL_SCANCODE_W))
    {
        moveVector.y = 1;
    }
    if (Input::GetKey(SDL_SCANCODE_S))
    {
        moveVector.y = -1;
    }
    if (Input::GetKey(SDL_SCANCODE_A))
    {
        moveVector.x = -1;
    }
    if (Input::GetKey(SDL_SCANCODE_D))
    {
        moveVector.x = 1;
    }

    if (Input::GetKeyDown(SDL_SCANCODE_E))
    {
        Attack();
    }

    SetMovementDirection(moveVector);
}

void Player::Animating(SDL_Renderer* renderer)
{
	if (m_death)
	{
		m_gfx.ChangeAnimation(renderer, m_char_anim_info.death);

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

	if (m_right && !m_up) m_attack_collider.SetCollisionOffset({ m_attack_collider_offset.x, m_attack_collider_offset.y * -1 });
	else if (!m_right && !m_up) m_attack_collider.SetCollisionOffset({ m_attack_collider_offset.x * -1, m_attack_collider_offset.y * -1 });
	else if (m_right && m_up) m_attack_collider.SetCollisionOffset({ m_attack_collider_offset.x, m_attack_collider_offset.y });
	else if (!m_right && m_up) m_attack_collider.SetCollisionOffset({ m_attack_collider_offset.x * -1, m_attack_collider_offset.y });
}

void Player::ToggleNoClip()
{
	m_collider.SetActive(!m_collider.GetActive());
}
