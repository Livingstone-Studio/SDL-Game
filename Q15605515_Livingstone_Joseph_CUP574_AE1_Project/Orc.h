#pragma once

#include "Enemy.h"

class Orc : public Enemy
{
public:

	Orc();
	Orc(Vector2 position);
	Orc(Transform transform);

protected:
	
	string m_image_name{ "Orc" };
};

