#include "QuitButton.h"
#include "../Application/Game.h"


QuitButton::QuitButton()
	: Button()
{
	m_text_scaling = { 2,2 };
}

QuitButton::QuitButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_text_scaling = { 2,.75f };
}

void QuitButton::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		Transform t = m_transform;

		t.scale = m_scale;

		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, t));

		RenderText(renderer, camera, "Quit");
	}
}

void QuitButton::PressButton()
{
	Game::Quit();
}
