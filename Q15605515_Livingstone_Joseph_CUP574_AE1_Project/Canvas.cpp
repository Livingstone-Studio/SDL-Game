#include "Canvas.h"

#include "Camera.h"

Canvas::Canvas()
{
	// HUD

	// Health GFX
	m_hud_elements.push_back(new UIElement(TopLeft, {-.7f, .8f, 7, 7}, {192, 80, 48, 16}, { 256, 16, 48, 16 }));
	m_hud_elements.push_back(new UIElement(TopLeft, {-.9f, .8f, 3.8f, 3.8f }, {16, 192, 16, 16}, { 0, 0, 0, 0 }));
	
	// Energy GFX
	m_hud_elements.push_back(new UIElement(TopLeft, { -.75f, .6f, 5, 5 }, { 192, 80, 48, 16 }, { 464, 16, 48, 16 }));
	m_hud_elements.push_back(new UIElement(TopLeft, { -.9f, .6f, 3, 3.5}, {64, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Hunger GFX
	m_hud_elements.push_back(new UIElement(TopRight, { .775f, .63f, 5, 5 }, { 128, 80, 16, 48 }, { 464, 480, 16, 48 }));
	m_hud_elements.push_back(new UIElement(TopRight, { .7875f, .4f, 3, 3 }, {32, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Thirst GFX
	m_hud_elements.push_back(new UIElement(TopRight, {.9f, .63f, 5, 5}, { 128, 80, 16, 48}, { 672, 144, 16, 48 }));
	m_hud_elements.push_back(new UIElement(TopRight, { .9f, .4f, 3, 3 }, {48, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Inventory GFX
	m_hud_elements.push_back(new UIElement(Bottom, { 0, -.8f, 6.5f, 6.5f }, { 16, 208, 48, 16 }, { 16, 224, 48, 16 }));

	// Inventory Selection GFX
	m_hud_elements.push_back(new UIElement(BottomLeft, { -.205f, -.8f, 6.25f, 6.25f }, { 64, 208, 16, 16 }, { 0, 0, 0, 0 }));
	
	// WASD Keys
	m_hud_elements.push_back(new UIElement(BottomLeft, { -.75f, -.52f, 8, 8 }, { 89, 208, 7, 10 }, { 0, 0, 0, 0 }));
	m_hud_elements.push_back(new UIElement(BottomLeft, { -.875f, -.8f, 8, 8 }, { 81, 216, 7, 10 }, { 0, 0, 0, 0 }));
	m_hud_elements.push_back(new UIElement(BottomLeft, { -.75f, -.8f, 8, 8 }, { 89, 216, 7, 10 }, { 0, 0, 0, 0 }));
	m_hud_elements.push_back(new UIElement(BottomLeft, { -.625f, -.8f, 8, 8 }, { 97, 216, 7, 10 }, { 0, 0, 0, 0 }));

	// Action Keys
	m_hud_elements.push_back(new UIElement(BottomRight, { .5f, -.8f, 8, 8 }, { 89, 227, 7, 10 }, { 0, 0, 0, 0 }));
	m_hud_elements.push_back(new UIElement(BottomRight, { .625f, -.8f, 8, 8 }, { 105, 227, 7, 10 }, { 0, 0, 0, 0 }));
	m_hud_elements.push_back(new UIElement(BottomRight, { .75f, -.8f, 8, 8 }, { 129, 208, 7, 10 }, { 0, 0, 0, 0 }));
	m_hud_elements.push_back(new UIElement(BottomRight, { .875f, -.8f, 8, 8 }, { 137, 208, 7, 10 }, { 0, 0, 0, 0 }));

	// Inventory Icon
	m_hud_elements.push_back(new UIElement(BottomLeft, { 0.005f, -.9f, 3, 3 }, { 0, 192, 16, 16 }, { 0, 0, 0, 0 }));
	
	// In Game Menu

	// Panels

	m_in_game_menu_elements.push_back(new UIElement(TopLeft, { -.6975f, .8f, 4.5f, 4.5f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }));

	// Icons
	m_in_game_menu_elements.push_back(new MuteButton(TopLeft, { -.85f, .8f, 2.75f, 2.75f }, { 0, 256, 16, 16 }, { 0, 0, 0, 0 }));
	m_in_game_menu_elements.push_back(new SaveButton(TopLeft, { -.75f, .8f, 2.75f, 2.75f }, { 0, 240, 16, 16 }, { 0, 0, 0, 0 }));
	m_in_game_menu_elements.push_back(new SettingsButton(TopLeft, { -.65f, .8f, 2.75f, 2.75f }, { 0, 208, 16, 16 }, { 0, 0, 0, 0 }));
	m_in_game_menu_elements.push_back(new SystemSettings(TopLeft, { -.55f, .8f, 2.75f, 2.75f }, { 0, 224, 16, 16 }, { 0, 0, 0, 0 }));


}

Canvas::~Canvas()
{
	//if (m_hud_elements.size() > 0)
	//{
	//	for (int i = 0; i < m_hud_elements.size(); i++)
	//	{
	//		if (m_hud_elements[i] != nullptr)
	//		{
	//			delete m_hud_elements[i];
	//		}
	//	}

	//	m_hud_elements.clear();
	//}
}

void Canvas::Start()
{
	for (int i = 0; i < m_hud_elements.size(); i++)
	{
		if (m_hud_elements[i] != nullptr)
		{
			if (!m_hud_elements[i]->IsInitialized())
			{
				m_hud_elements[i]->Start();
			}
		}
	}

	for (int i = 0; i < m_in_game_menu_elements.size(); i++)
	{
		if (m_in_game_menu_elements[i] != nullptr)
		{
			if (!m_in_game_menu_elements[i]->IsInitialized())
			{
				m_in_game_menu_elements[i]->Start();
			}
		}
	}
}

void Canvas::RenderStart(SDL_Renderer* renderer)
{
	for (int i = 0; i < m_hud_elements.size(); i++)
	{
		if (m_hud_elements[i] != nullptr)
		{
			if (!m_hud_elements[i]->IsRenderInitialized())
			{
				m_hud_elements[i]->RenderStart(renderer);
			}
		}
	}

	for (int i = 0; i < m_in_game_menu_elements.size(); i++)
	{
		if (m_in_game_menu_elements[i] != nullptr)
		{
			if (!m_in_game_menu_elements[i]->IsRenderInitialized())
			{
				m_in_game_menu_elements[i]->RenderStart(renderer);
			}
		}
	}
}

void Canvas::Update(Camera camera)
{
    // Do ui updates here

	switch (m_current_ui) 
	{
	case HUD:
		for (int i = 0; i < m_hud_elements.size(); i++)
		{
			if (m_hud_elements[i] != nullptr)
			{
				m_hud_elements[i]->Update(camera);
			}
		}

		if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) 
		{
			m_current_ui = InGameMenu;
		}
		break;
	case InGameMenu:
		for (int i = 0; i < m_in_game_menu_elements.size(); i++)
		{
			if (m_in_game_menu_elements[i] != nullptr)
			{
				m_in_game_menu_elements[i]->Update(camera);
			}
		}

		if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			m_current_ui = HUD;
		}
		break;
	}
}

void Canvas::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
    // Do Render Here

	switch (m_current_ui)
	{
	case HUD:
		for (int i = 0; i < m_hud_elements.size(); i++)
		{
			if (m_hud_elements[i] != nullptr)
			{
				m_hud_elements[i]->RenderUpdate(renderer, camera);
			}
		}
		break;
	case InGameMenu:
		for (int i = 0; i < m_in_game_menu_elements.size(); i++)
		{
			if (m_in_game_menu_elements[i] != nullptr)
			{
				m_in_game_menu_elements[i]->RenderUpdate(renderer, camera);
			}
		}
		break;
	}
}
