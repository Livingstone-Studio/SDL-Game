#include "MuteButton.h"

#include "AudioManager.h"

MuteMusicButton::MuteMusicButton()
	:Button()
{
}

MuteMusicButton::MuteMusicButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void MuteMusicButton::PressButton()
{
	AudioManager::ToggleMusic();
}
