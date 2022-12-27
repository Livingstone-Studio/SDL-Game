#include "DebugButton.h"

#include "Game.h"

DebugButton::DebugButton()
	:Button()
{
}

DebugButton::DebugButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void DebugButton::PressButton()
{
	Game::ToggleDebug();
}
