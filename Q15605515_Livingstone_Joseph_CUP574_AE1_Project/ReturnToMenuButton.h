#pragma once

#include "Button.h"

class ReturnToMenuButton : public Button
{
public:

	ReturnToMenuButton();
	ReturnToMenuButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void PressButton() override;

protected:



};

