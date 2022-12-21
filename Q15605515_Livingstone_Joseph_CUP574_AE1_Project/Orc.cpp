#include "Orc.h"

Orc::Orc()
{
}

Orc::Orc(Vector2 position)
{
	m_transform.position = position;
}

Orc::Orc(Transform transform)
{
	m_transform = transform;
}
