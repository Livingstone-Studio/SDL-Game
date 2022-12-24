#include "SaveButton.h"

SaveButton::SaveButton()
	:Button()
{
}

SaveButton::SaveButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void SaveButton::PressButton()
{
	cout << "Save" << endl;
}