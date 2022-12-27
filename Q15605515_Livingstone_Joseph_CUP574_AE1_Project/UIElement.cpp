#include "UIElement.h"

#include "Camera.h"

UIElement::UIElement()
	: m_src_one{ 0,0,5,5 }, m_src_two{0,0,5,5}
{
	m_gfx.UpdateSRC(m_src_one, m_src_two);
}

UIElement::UIElement(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, string text)
	: m_anchor_point{ anchorPoint }, m_transform{ animDES }, m_src_one{ animOneSRC }, m_src_two{ animTwoSRC }, m_text{ text }
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

void UIElement::Update(Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		m_gfx.Update();
	}
}

void UIElement::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, m_transform));

		RenderText(renderer, camera, m_text);
	}
}

void UIElement::RenderText(SDL_Renderer* renderer, Camera camera, string text)
{
	if (text.length() > 0) 
	{
		SDL_Surface* textSurface = TTF_RenderText_Blended(AssetLoader::GetRetroFont(), text.c_str(), { 255,255,255,255 });

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);

		Transform t = m_transform;

		t.position += m_text_offset;

		t = camera.ConvertToUISpace(m_anchor_point, t);

		SDL_Rect fontRect = { t.position.x, t.position.y, 32 * camera.GetWindowNormalized().x, 32 * camera.GetWindowNormalized().y };

		fontRect.x -= fontRect.w / 2;
		fontRect.y -= fontRect.h / 2;

		SDL_RenderCopy(renderer, texture, NULL, &fontRect);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(textSurface);
	}
}
