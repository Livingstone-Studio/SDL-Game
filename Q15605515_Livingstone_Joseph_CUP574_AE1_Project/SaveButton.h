#pragma once

#include "Button.h"

class SaveButton : public Button
{
public:

	SaveButton();
	SaveButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void PressButton() override;

protected:



};
