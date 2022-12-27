#include "Slider.h"

#include "Camera.h"
#include "Time.h"

Slider::Slider()
	: UIElement()
{
	m_text_offset = m_slider_text_offset;
}

Slider::Slider(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: UIElement(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_text_offset = m_slider_text_offset;
}

Slider::~Slider()
{
}

void Slider::Update(Camera camera)
{
	UIElement::Update(camera);
}

void Slider::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, m_transform));

		RenderText(renderer, camera, to_string((int)(m_custom_scale.x * 100)));
	}
}

void Slider::SetSize(float value)
{
	m_custom_scale.x = value;
	m_gfx.SetCustomScaleAnimTwo(m_custom_scale);
}
