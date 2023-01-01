#include "ReturnToMenuButton.h"

#include "Game.h"

ReturnToMenuButton::ReturnToMenuButton()
	:Button()
{
	m_text_scaling = { 2,2 };
}

ReturnToMenuButton::ReturnToMenuButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, string t)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_text = t;
	m_text_scaling = { 4,1 };
}

void ReturnToMenuButton::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		Transform t = m_transform;

		t.scale = m_scale;

		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, t));

		RenderText(renderer, camera, m_text);
	}
}
void ReturnToMenuButton::PressButton()
{
	Game::ReturnToMenu();
}