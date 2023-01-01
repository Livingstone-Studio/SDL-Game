#include "MuteEffectButton.h"

#include "AudioManager.h"
#include "Camera.h"

MuteEffectButton::MuteEffectButton()
	:Button()
{
}

MuteEffectButton::MuteEffectButton(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: Button(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
}

bool MuteEffectButton::CheckMouseOnButton(Camera camera)
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

void MuteEffectButton::PressButton()
{
	AudioManager::ToggleEffects();
}