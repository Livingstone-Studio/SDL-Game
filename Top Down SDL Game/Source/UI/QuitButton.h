#pragma once

#include "Button.h"

class QuitButton : public Button
{
public:

	QuitButton();
	QuitButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	virtual void PressButton() override;
};

