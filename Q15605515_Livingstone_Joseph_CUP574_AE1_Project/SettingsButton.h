#pragma once

#include "Button.h"

class SettingsButton : public Button
{
public:

	SettingsButton();
	SettingsButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void PressButton() override;
};

