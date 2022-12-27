#pragma once

#include "Character.h"
#include "Input.h"

class Collectable;

class Player : public Character
{
public:

	Player();
	Player(Vector2 position);
	Player(Transform transform);

	~Player();

	virtual void InitializeHUD(vector<Slider*> elements);

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera);

	virtual void InputUpdate(float deltaTime);

	virtual void Update(float deltaTime) override;

	virtual void Animating(SDL_Renderer* renderer);

	virtual void ToggleNoClip();

	virtual void Eat(float amount);
	virtual void Drink(float amount);

	virtual bool AddToInventory(Collectable c);

	virtual void TakeDamage(int health) override;

protected:

	float m_default_move_speed{ m_move_speed };
	float m_move_sprint{ m_move_speed * 2 };

	float m_max_energy{ 5 };
	float m_energy{ 5 };
	float m_energy_regen_multiplier{ 1.2f };
	float m_sprint_usage_multiplier{ 1.2f };

	float m_max_hungry{ 5 };
	float m_hungry{ 5 };
	float m_hungry_usage_multiplier{ 1.2f };

	float m_max_thirst{ 5 };
	float m_thirst{ 5 };
	float m_thirst_usage_multiplier{ 1.2f };

	string m_image_name{ "Gobbie" };

	Slider* m_health_bar{ nullptr };
	Slider* m_energy_bar{ nullptr };
	Slider* m_thirst_bar{ nullptr };
	Slider* m_hunger_bar{ nullptr };
};
