#pragma once

#include "Button.h"

class MuteEffectButton : public Button
{
public:

	MuteEffectButton();
	MuteEffectButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual void PressButton() override;

protected:



};
