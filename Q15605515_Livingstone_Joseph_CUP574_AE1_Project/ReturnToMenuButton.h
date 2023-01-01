#pragma once

#include "Button.h"

class ReturnToMenuButton : public Button
{
public:

	ReturnToMenuButton();
	ReturnToMenuButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, string t = "");

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	virtual void PressButton() override;

protected:

	string m_text{ "" };

};

