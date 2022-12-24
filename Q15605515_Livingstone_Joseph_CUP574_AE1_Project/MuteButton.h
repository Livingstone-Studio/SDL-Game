#pragma once

#include "Button.h"

class MuteButton : public Button
{
public:

	MuteButton();
	MuteButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void PressButton() override;
};