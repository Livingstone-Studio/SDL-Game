#pragma once

#include "Character.h"
#include "../Application/Input.h"

class Collectable;

class Player : public Character
{
public:

	Player();
	Player(Vector2 position);
	Player(Transform transform);

	~Player();

	virtual void InitializeHUD(vector<Slider*> elements, UIElement* score);

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera);

	virtual void InputUpdate(float deltaTime);

	virtual void Update(float deltaTime) override;

	virtual void Animating(SDL_Renderer* renderer);

	virtual void ToggleNoClip();

	virtual bool AddCollectable(Collectable c);

	virtual void TakeDamage(int health) override;

protected:

	float m_default_move_speed{ m_move_speed };
	float m_move_sprint{ m_move_speed * 2 };

	float m_max_energy{ 5 };
	float m_energy{ 5 };
	float m_energy_regen_multiplier{ 1.2f };
	float m_sprint_usage_multiplier{ 1.2f };

	string m_image_name{ "Gobbie" };

	Slider* m_health_bar{ nullptr };
	Slider* m_energy_bar{ nullptr };

	UIElement* m_score_ui{ nullptr };

};
