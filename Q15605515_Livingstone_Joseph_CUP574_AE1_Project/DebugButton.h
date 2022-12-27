#pragma once

#include "Button.h"

class DebugButton : public Button
{
public:

	DebugButton();
	DebugButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void PressButton() override;

protected:



};

