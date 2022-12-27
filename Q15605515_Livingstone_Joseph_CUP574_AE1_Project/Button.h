#pragma once

#include "UIElement.h"

class Button : public UIElement
{
public:

	Button();
	Button(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void Update(Camera camera) override;

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	virtual bool CheckMouseOnButton(Camera camera);

	virtual void PressButton();

	virtual bool Pressed() { return m_pressed; }
	virtual void SetPressed(bool state) { m_pressed = state; }

protected:

	bool m_pressed{ false };
	bool m_hovering{ false };

	Vector2 m_scale{ 7.5f,7.5f };

	Vector2 m_default_scale{ 7.5f,7.5f };
	Vector2 m_hover_scale{ 3.5f,3.5f };
	Vector2 m_pressed_scale{ 2.5f,2.5f };


	Vector2 m_offset{ 0.0f,0.005f };

};