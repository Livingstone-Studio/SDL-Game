#include "SystemSettings.h"

SystemSettings::SystemSettings()
	: Button()
{
}

SystemSettings::SystemSettings(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void SystemSettings::PressButton()
{
	cout << "System" << endl;
}
