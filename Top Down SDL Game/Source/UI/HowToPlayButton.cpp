#include "HowToPlayButton.h"
#include "../Application/Game.h"


HowToPlayButton::HowToPlayButton()
	: Button()
{
	m_text_scaling = { 2,2 };
}

HowToPlayButton::HowToPlayButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, Canvas* canvas, Vector2 text_size)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_text_scaling = text_size;
	m_canvas = canvas;
}

void HowToPlayButton::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		Transform t = m_transform;

		t.scale = m_scale;

		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, t));

		RenderText(renderer, camera, "How To Play");
	}
}

void HowToPlayButton::PressButton()
{
	if (m_canvas != nullptr) m_canvas->ChangeState(HowToPlay);
}
