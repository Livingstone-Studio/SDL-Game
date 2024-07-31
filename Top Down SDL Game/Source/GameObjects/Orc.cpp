#include "Orc.h"

Orc::Orc()
{
	m_char_anim_info = m_charAnimInfo;
	m_hit_area = m_collider;
	m_hit_area.SetActive(true);
}

Orc::Orc(Vector2 position)
{
	m_char_anim_info = m_charAnimInfo;
	m_transform.position = position;
	m_hit_area = m_collider;
	m_hit_area.SetActive(true);
}

Orc::Orc(Transform transform)
{
	m_char_anim_info = m_charAnimInfo;
	m_transform = transform;
	m_hit_area = m_collider;
	m_hit_area.SetActive(true);
}