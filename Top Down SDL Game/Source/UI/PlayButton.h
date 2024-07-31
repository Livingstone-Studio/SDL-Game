#pragma once

#include "Button.h"

class PlayButton : public Button
{
public:

	PlayButton();
	PlayButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	virtual void PressButton() override;

};