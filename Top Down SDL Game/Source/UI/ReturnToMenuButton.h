#pragma once

#include "Button.h"

class ReturnToMenuButton : public Button
{
public:

	ReturnToMenuButton();
	ReturnToMenuButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, string t = "", bool icon = false);

	virtual bool CheckMouseOnButton(Camera camera);

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	virtual void PressButton() override;

protected:

	bool m_icon{ false };

	string m_text{ "" };

};

