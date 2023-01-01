#pragma once

#include "Button.h"

class MuteMusicButton : public Button
{
public:

	MuteMusicButton();
	MuteMusicButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC);

	virtual bool CheckMouseOnButton(Camera camera);

	virtual void PressButton() override;
};