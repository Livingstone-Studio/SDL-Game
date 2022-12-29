#include "PlayButton.h"

#include "Game.h"

PlayButton::PlayButton()
	: Button()
{
	m_text_scaling = { 2,2 };
}

PlayButton::PlayButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_text_scaling = { 1.5f,1.5f };
}


void PlayButton::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		Transform t = m_transform;

		t.scale = m_scale;

		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, t));

		RenderText(renderer, camera, "Play");
	}
}


void PlayButton::PressButton()
{
	Game::Play();
}
