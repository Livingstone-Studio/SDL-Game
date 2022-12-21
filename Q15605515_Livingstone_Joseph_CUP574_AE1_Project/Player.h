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

	virtual void Animating(SDL_Renderer* renderer);

protected:

	string m_image_name{ "Gobbie" };

};
