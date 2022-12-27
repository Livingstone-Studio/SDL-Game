#include "Slider.h"

#include "Camera.h"
#include "Time.h"

Slider::Slider()
	: UIElement()
{
}

Slider::Slider(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: UIElement(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

Slider::~Slider()
{
}

void Slider::Update(Camera camera)
{
	UIElement::Update(camera);
}

void Slider::SetSize(float value)
{
	m_custom_scale.x = value;
	m_gfx.SetCustomScaleAnimTwo(m_custom_scale);
}
