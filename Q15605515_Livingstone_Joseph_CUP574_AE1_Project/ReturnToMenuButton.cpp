#include "ReturnToMenuButton.h"

#include "Game.h"

ReturnToMenuButton::ReturnToMenuButton()
	:Button()
{
}

ReturnToMenuButton::ReturnToMenuButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void ReturnToMenuButton::PressButton()
{
	Game::Quit();
}
