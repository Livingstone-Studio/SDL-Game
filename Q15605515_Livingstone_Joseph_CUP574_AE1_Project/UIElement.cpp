#include "UIElement.h"

#include "Camera.h"

UIElement::UIElement()
	: m_src_one{ 0,0,5,5 }, m_src_two{0,0,5,5}
{
	m_gfx.UpdateSRC(m_src_one, m_src_two);
}

UIElement::UIElement(Transform transform, Transform t)
	: m_src_one{transform}, m_src_two{ t }
{
	m_gfx.UpdateSRC(m_src_one, m_src_two);
}

UIElement::~UIElement()
{
}

void UIElement::Start()
{
	m_initialized = true;
}

//row{ r }, spriteCount{ sC }, animTimeBetween{ t }, start{ s }, looping{ l }, eventTrigger{ e, i }
void UIElement::RenderStart(SDL_Renderer* renderer)
{
	m_gfx.InitAnim(renderer, "UIBars", { "ui_bars", {1,1,0,0,false}, {1,1,0,0,false} });
	m_render_initialized = true;
}

void UIElement::Update()
{
	if (m_render_initialized && !m_deletion)
	{
		m_gfx.Update();
	}
}

void UIElement::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion)
	{
		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_transform));
	}
}
