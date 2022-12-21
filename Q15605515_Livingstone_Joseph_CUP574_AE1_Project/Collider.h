#pragma once

#include "Structs.h"


class Collider
{
public:

	Collider();
	Collider(bool active, bool trigger, Vector2 offset = { 0,0 });

	~Collider();

	void SetActive(bool active) { m_active = active; }
	bool GetActive() { return m_active; }

	virtual CollisionInfo CollisionCheck(bool trigger, Transform c1, Transform c2);

	bool IsTrigger() { return m_trigger; }

	void SetCollisionOffset(Vector2 o) { m_offset = o; }
	Vector2 GetCollisionOffset() { return m_offset; }

protected:

	bool m_active{ false };

	bool m_trigger{ false };

	Vector2 m_offset{ 0,0 };

	Vector2 m_c1_min;
	Vector2 m_c1_max;

	Vector2 m_c2_min;
	Vector2 m_c2_max;
};