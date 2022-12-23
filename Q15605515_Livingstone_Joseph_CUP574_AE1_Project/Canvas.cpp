#include "Canvas.h"

#include "Camera.h"

Canvas::Canvas()
{
	m_elements.push_back(new UIElement({80, 16, 48, 16}, {256, 16, 48, 16}));
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
