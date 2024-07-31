#pragma once

#include "UIElement.h"

class Slider : public UIElement
{
public:

	Slider();
	Slider(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	~Slider();

	virtual void Update(Camera camera) override;

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	void SetSize(float value);

protected:

	Vector2 m_slider_text_offset{ 0,-0.1f };

	bool clear = false;
	Vector2 m_custom_scale{ 1,1 };

};