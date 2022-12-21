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
	m_attacking = false;
}

void Slime::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_charAnimInfo.idleR);

	GameObject::RenderStart(renderer, camera);
}
