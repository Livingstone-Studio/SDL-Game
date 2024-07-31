#include "Collider.h"

Collider::Collider()
	: Collider(false, false)
{
}

Collider::Collider(bool active, bool trigger, Vector2 offset)
	: m_active{ active }, m_trigger{ trigger }, m_offset{ offset }
{
}

Collider::~Collider()
{
}

CollisionInfo Collider::CollisionCheck(bool trigger, Transform c1, Transform c2)
{
	// AABB c1 = this gameobject transform.

	m_c1_min = c1.position - c1.scale;
	m_c1_max = c1.position + c1.scale;

	m_c2_min = c2.position - c2.scale;
	m_c2_max = c2.position + c2.scale;

	if (m_c1_min.x > m_c2_max.x || m_c1_max.x < m_c2_min.x) return { false, trigger, c1, c2 };
	if (m_c1_min.y > m_c2_max.y || m_c1_max.y < m_c2_min.y) return { false, trigger, c1, c2 };

	return { true, trigger, c1, c2 };
}