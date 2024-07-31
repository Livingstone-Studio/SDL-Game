#pragma once

#include "PlayButton.h"

class PlayLevelTwo : public PlayButton
{
public:

	PlayLevelTwo();
	PlayLevelTwo(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	virtual void PressButton() override;

};

