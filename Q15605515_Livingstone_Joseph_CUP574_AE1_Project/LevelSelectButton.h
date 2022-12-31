#pragma once

#include "Button.h"

class LevelSelectButton : public Button
{
public:

	LevelSelectButton();
	LevelSelectButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, Canvas* canvas, Vector2 text_size = { 1,1 });

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera) override;

	virtual void PressButton() override;

protected:

	Canvas* m_canvas{ nullptr };
};

