#include "Button.h"

#include "Camera.h"

Button::Button()
	: UIElement()
{
}

Button::Button(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: UIElement(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

void Button::Update(Camera camera)
{
	if (Input::LeftMousePress()) 
	{
		if (CheckMouseOnButton(camera))
		{
			PressButton();
		}
	}	

	UIElement::Update(camera);
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
