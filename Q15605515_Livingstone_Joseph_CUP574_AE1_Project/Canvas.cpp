#include "Canvas.h"

#include "Camera.h"

Canvas::Canvas()
{
	// Health GFX
	m_elements.push_back(new UIElement({-.7f, .8f, 7, 7}, {192, 80, 48, 16}, { 256, 16, 48, 16 }));
	m_elements.push_back(new UIElement({-.9f, .8f, 3.8f, 3.8f }, {16, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Energy GFX
	m_elements.push_back(new UIElement({ -.75f, .6f, 5, 5 }, { 192, 80, 48, 16 }, { 464, 16, 48, 16 }));
	m_elements.push_back(new UIElement({ -.9f, .6f, 3, 3.5}, {64, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Hunger GFX
	m_elements.push_back(new UIElement({ .775f, .63f, 5, 5 }, { 128, 80, 16, 48 }, { 464, 480, 16, 48 }));
	m_elements.push_back(new UIElement({ .7875f, .4f, 3, 3 }, {32, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Thirst GFX
	m_elements.push_back(new UIElement({.9f, .63f, 5, 5}, { 128, 80, 16, 48}, { 672, 144, 16, 48 }));
	m_elements.push_back(new UIElement({ .9f, .4f, 3, 3 }, {48, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Inventory GFX
	m_elements.push_back(new UIElement({ 0, -.8f, 6.5f, 6.5f }, { 16, 208, 48, 16 }, { 16, 224, 48, 16 }));

	// Inventory Selection GFX
	m_elements.push_back(new UIElement({ -.19f, -.8f, 6.5f, 6.5f }, { 64, 208, 16, 16 }, { 0, 0, 0, 0 }));
	
	// WASD Keys
	m_elements.push_back(new UIElement({ -.75f, -.52f, 8, 8 }, { 89, 208, 7, 10 }, { 0, 0, 0, 0 }));
	m_elements.push_back(new UIElement({ -.875f, -.8f, 8, 8 }, { 81, 216, 7, 10 }, { 0, 0, 0, 0 }));
	m_elements.push_back(new UIElement({ -.75f, -.8f, 8, 8 }, { 89, 216, 7, 10 }, { 0, 0, 0, 0 }));
	m_elements.push_back(new UIElement({ -.625f, -.8f, 8, 8 }, { 97, 216, 7, 10 }, { 0, 0, 0, 0 }));

	// Action Keys
	m_elements.push_back(new UIElement({ .5f, -.8f, 8, 8 }, { 89, 227, 7, 10 }, { 0, 0, 0, 0 }));
	m_elements.push_back(new UIElement({ .625f, -.8f, 8, 8 }, { 105, 227, 7, 10 }, { 0, 0, 0, 0 }));
	m_elements.push_back(new UIElement({ .75f, -.8f, 8, 8 }, { 129, 208, 7, 10 }, { 0, 0, 0, 0 }));
	m_elements.push_back(new UIElement({ .875f, -.8f, 8, 8 }, { 137, 208, 7, 10 }, { 0, 0, 0, 0 }));
}

Canvas::~Canvas()
{
}

void Canvas::Start()
{
	for (int i = 0; i < m_elements.size(); i++)
	{
		if (m_elements[i] != nullptr)
		{
			if (!m_elements[i]->IsInitialized())
			{
				m_elements[i]->Start();
			}
		}
	}
}

void Canvas::RenderStart(SDL_Renderer* renderer)
{
	for (int i = 0; i < m_elements.size(); i++)
	{
		if (m_elements[i] != nullptr)
		{
			if (!m_elements[i]->IsRenderInitialized())
			{
				m_elements[i]->RenderStart(renderer);
			}
		}
	}
}

void Canvas::Update()
{
    // Do ui updates here

	for (int i = 0; i < m_elements.size(); i++)
	{
		if (m_elements[i] != nullptr)
		{
			m_elements[i]->Update();
		}
	}
}

void Canvas::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
    // Do Render Here

	for (int i = 0; i < m_elements.size(); i++)
	{
		if (m_elements[i] != nullptr)
		{
			m_elements[i]->RenderUpdate(renderer, camera);
		}
	}
}
