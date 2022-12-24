#include "SettingsButton.h"

SettingsButton::SettingsButton()
	: Button()
{
}

SettingsButton::SettingsButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void SettingsButton::PressButton()
{
	cout << "Settings" << endl;
}
