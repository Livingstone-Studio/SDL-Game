#pragma once

#include <SDL_image.h>

#include "Structs.h"
#include "AssetLoader.h"

#include "Animation.h"

#include <vector>

class Canvas;

enum AnchorPosition {
	TopLeft, Top, TopRight,
	Left, Middle, Right,
	BottomLeft, Bottom, BottomRight
};

class UIElement
{
public:

	UIElement();
	UIElement(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC, string text = "", Vector2 text_scaling = { 1,1 }, Vector2 text_offset = { 0,0 });
	
	~UIElement();

	AnchorPosition m_anchor_point{ Middle };

	virtual void Start();

	virtual void RenderStart(SDL_Renderer* renderer);

	virtual void Update(Camera camera);

	virtual void RenderUpdate(SDL_Renderer* renderer, Camera camera);

	virtual void RenderText(SDL_Renderer* renderer, Camera camera, string text);

	virtual Transform GetTransform() { return m_transform; }

	virtual Animation GetImage() { return m_gfx; }

	virtual bool IsInitialized() { return m_initialized; }

	virtual bool IsRenderInitialized() { return m_render_initialized; }

	AnchorPosition GetAnchorPoint() { return m_anchor_point; }

	void SetActive(bool s) { m_active = s; }
	bool IsActive() { return m_active; }

	void SetText(string text) { m_text = text; }

protected:

	string m_text{ "" };

	Vector2 m_text_offset{ 0,0 };

	bool m_active{ true };

	Animation m_gfx;

	bool m_initialized{ false };

	bool m_render_initialized{ false };

	bool m_deletion{ false };

	Transform m_transform{ -.7f,.8f,7,7 };

	Transform m_src_one{ 0,0,10,10 };
	Transform m_src_two{ 0,0,10,10 };

	Vector2 m_text_scaling{ 1,1 };

};

