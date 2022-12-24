#pragma once

#include "UIElement.h"

class Button : public UIElement
{
public:

	Button();
	Button(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void Update(Camera camera) override;

	virtual bool CheckMouseOnButton(Camera camera);

	virtual void PressButton();

protected:

	Vector2 m_scale{ 7.5f,7.5f };
	Vector2 m_offset{ 0.0f,0.005f };

};