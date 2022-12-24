#include "MuteButton.h"

#include "AudioManager.h"

MuteButton::MuteButton()
	:Button()
{
}

MuteButton::MuteButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void MuteButton::PressButton()
{
	AudioManager::ToggleSound();
}
