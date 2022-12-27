#include "Player.h"

#include "Collectable.h"

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

void Player::InitializeHUD(vector<Slider*> elements)
{
	m_health_bar = elements[0];
	m_energy_bar = elements[1];
	m_thirst_bar = elements[2];
	m_hunger_bar = elements[3];
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

void Player::Update(float deltaTime)
{
	if (Input::GetKey(SDL_SCANCODE_LSHIFT) && m_energy > 0)
	{
		m_energy -= deltaTime * m_sprint_usage_multiplier;

		m_move_speed = m_move_sprint;

		if (m_energy < 0) m_energy = 0;
	}
	else 
	{
		m_move_speed = m_default_move_speed;
	}

	if (!Input::GetKey(SDL_SCANCODE_LSHIFT) && m_energy < m_max_energy && (m_hungry > 0 || m_thirst > 0))
	{
		float regenAmount = deltaTime * m_energy_regen_multiplier;

		if (m_hungry > 0) 
		{
			regenAmount *= m_hungry_usage_multiplier;
			m_hungry -= deltaTime * m_hungry_usage_multiplier;
		}
		if (m_thirst > 0) 
		{
			regenAmount *= m_thirst_usage_multiplier;
			m_thirst -= deltaTime * m_thirst_usage_multiplier;
		}

		if (m_hungry < 0) m_hungry = 0;
		if (m_thirst < 0) m_thirst = 0;

		m_energy += regenAmount;

		if (m_energy > m_max_energy) m_energy = m_max_energy;


		if (m_hunger_bar != nullptr) m_hunger_bar->SetSize(m_hungry / m_max_hungry);
		else cout << "No bar" << endl;

		if (m_thirst_bar != nullptr) m_thirst_bar->SetSize(m_thirst / m_max_thirst);
		else cout << "No bar" << endl;
	}


	if (m_energy_bar != nullptr) m_energy_bar->SetSize(m_energy / m_max_energy);
	else cout << "No bar" << endl;

	Character::Update(deltaTime);
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

void Player::Eat(float amount)
{
	m_hungry += amount;

	if (m_hungry > m_max_hungry) m_hungry = m_max_hungry;

	if (m_hunger_bar != nullptr) m_hunger_bar->SetSize(m_hungry/m_max_hungry);
	else cout << "No bar" << endl;
}

void Player::Drink(float amount)
{
	m_thirst += amount;

	if (m_thirst > m_max_thirst) m_thirst = m_max_thirst;

	if (m_thirst_bar != nullptr) m_thirst_bar->SetSize(m_thirst / m_max_thirst);
	else cout << "No bar" << endl;
}

bool Player::AddToInventory(Collectable c)
{
	cout << "Added collectable to inventory" << endl;
	return true;
}

void Player::TakeDamage(int health)
{

	Character::TakeDamage(health);


	if (m_health_bar != nullptr) m_health_bar->SetSize((float)m_health / (float)m_max_health);
	else cout << "No bar" << endl;
}
