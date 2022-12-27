#pragma once

#include "UIElement.h"

class Slider : public UIElement
{
public:

	Slider();
	Slider(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	~Slider();

	virtual void Update(Camera camera) override;

	void SetSize(float value);

protected:

	bool clear = false;
	Vector2 m_custom_scale{ 1,1 };

};