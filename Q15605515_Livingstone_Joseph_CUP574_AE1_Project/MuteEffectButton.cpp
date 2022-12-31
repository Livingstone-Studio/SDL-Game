#include "MuteEffectButton.h"

#include "AudioManager.h"

MuteEffectButton::MuteEffectButton()
	:Button()
{
}

MuteEffectButton::MuteEffectButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void MuteEffectButton::PressButton()
{
	AudioManager::ToggleEffects();
}