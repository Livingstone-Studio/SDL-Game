#pragma once

#include "Button.h"

class MuteEffectButton : public Button
{
public:

	MuteEffectButton();
	MuteEffectButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual bool CheckMouseOnButton(Camera camera);

	virtual void PressButton() override;

protected:



};
