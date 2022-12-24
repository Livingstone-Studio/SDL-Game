#pragma once

#include "Button.h"

class SystemSettings : public Button
{
public:

	SystemSettings();
	SystemSettings(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void PressButton() override;
};

