#include "ReturnToMenuButton.h"
#include "../Application/Game.h"


ReturnToMenuButton::ReturnToMenuButton()
	:Button()
{
	m_text_scaling = { 2,2 };
}

ReturnToMenuButton::ReturnToMenuButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, string t, bool icon)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_text = t;
	m_text_scaling = { 4,1 };
	m_icon = icon;
}

bool ReturnToMenuButton::CheckMouseOnButton(Camera camera)
{
	if (m_icon) 
	{
		Transform t = m_transform;
		t = t.position + m_offset;

		t.scale *= m_default_scale;
		t.scale *= m_transform.scale;

		t = camera.ConvertToUISpace(m_anchor_point, t);

		Vector2 m = Input::GetMousePosition();

		Vector2 box_min = t.position - t.scale;
		Vector2 box_max = t.position + t.scale;

		if (box_min.x > m.x || box_max.x < m.x) return false;
		if (box_min.y > m.y || box_max.y < m.y) return false;

		return true;
	}
	else 
	{
		Transform t = m_transform;
		t = t.position + m_offset;

		t.scale *= m_default_scale;
		t.scale *= m_transform.scale;

		Vector2 scale = { 5,2 };

		t.scale *= scale;

		t = camera.ConvertToUISpace(m_anchor_point, t);

		Vector2 m = Input::GetMousePosition();

		Vector2 box_min = t.position - t.scale;
		Vector2 box_max = t.position + t.scale;

		if (box_min.x > m.x || box_max.x < m.x) return false;
		if (box_min.y > m.y || box_max.y < m.y) return false;

		return true;
	}
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