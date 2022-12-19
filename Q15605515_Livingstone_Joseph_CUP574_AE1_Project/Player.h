#pragma once

#include "Character.h"
#include "Input.h"

class Player : public Character
{

public:

	Player();
	Player(Vector2 position);
	Player(Transform transform);

	~Player();

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera);

	virtual void InputUpdate(float deltaTime);

protected:

	string m_sprite_name{ "Gobbie" };

};
