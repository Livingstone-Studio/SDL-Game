#include "Button.h"

#include "Camera.h"

Button::Button()
	: UIElement()
{
	m_default_scale = m_transform.scale;
	m_scale = m_default_scale;
}

Button::Button(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: UIElement(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_default_scale = m_transform.scale;
	m_scale = m_default_scale;
}

void Button::Update(Camera camera)
{
	if (CheckMouseOnButton(camera))
	{
		if (!m_hovering) 
		{
			// Play hover sound / swap sprite to slightly smaller scaled
			AudioManager::PlayEffect("hoverStart");
			m_scale = m_hover_scale;
		}
		else if (m_pressed) 
		{
			m_scale = m_hover_scale;
			m_pressed = false;
		}
		m_hovering = true;


	}
	else
	{
		if (m_hovering)
		{
			// Play stop hover sound / swap sprite to default scaled
			AudioManager::PlayEffect("hoverStop");
			m_scale = m_default_scale;
		}

		m_hovering = false;
	}

	if (Input::LeftMousePress() && m_hovering) 
	{
		PressButton();
		// Play press sound / swap sprite to smallest scaled
		AudioManager::PlayEffect("press");

		m_scale = m_pressed_scale;

		m_pressed = true;
	}

	UIElement::Update(camera);
}

void Button::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		Transform t = m_transform;

		t.scale = m_scale;

		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, t));

		RenderText(renderer, camera, "");
	}
}

bool Button::CheckMouseOnButton(Camera camera)
{
	Transform t = m_transform;
	t = t.position + m_offset;
	t = camera.ConvertToUISpace(m_anchor_point, t);
	Vector2 m = Input::GetMousePosition();

	t.scale *= m_transform.scale;

	t.scale *= m_scale;

	Vector2 box_min = t.position - t.scale;
	Vector2 box_max = t.position + t.scale;

	if (box_min.x > m.x || box_max.x < m.x) return false;
	if (box_min.y > m.y || box_max.y < m.y) return false;

	return true;
}

void Button::PressButton()
{
	cout << "In box" << endl;
}
