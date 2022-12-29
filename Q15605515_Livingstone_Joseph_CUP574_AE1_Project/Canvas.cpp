#include "Canvas.h"

#include "Camera.h"
#include "Player.h"

#include "Game.h"

Canvas::Canvas()
{
	// Main Menu

	m_main_menu_elements.push_back(new UIElement(TopLeft, { 0, .6f, 5.0f, 5.0f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }, "Gobbie The Gobbo", { 8,2 }));
	
	m_main_menu_elements.push_back(new PlayButton(TopLeft, { 0, -.6f, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }));

	// HUD

	// Health GFX
	m_hud_elements.push_back(new Slider(TopLeft, { 0, .8f, 7, 7 }, { 192, 80, 48, 16 }, { 256, 16, 48, 16 }));
	m_hud_elements.push_back(new Slider(TopLeft, { 0, .6f, 5, 5 }, { 192, 80, 48, 16 }, { 464, 16, 48, 16 }));
	m_hud_elements.push_back(new Slider(TopRight, { .775f, .8f, 5, 5 }, { 192, 80, 48, 16 }, { 464, 352, 48, 16 }));
	m_hud_elements.push_back(new Slider(TopRight, {-.775f, .8f, 5, 5}, { 192, 80, 48, 16 }, { 672, 16, 48, 16 }));
	
	for (int i = 0; i < m_hud_elements.size(); i++)
	{
		if (m_hud_elements[i] != nullptr)
		{
			Slider* s = dynamic_cast<Slider*>(m_hud_elements[i]);

			if (s != nullptr) 
			{
				m_sliders.push_back(s);
			}
		}
	}

	m_hud_elements.push_back(new UIElement(TopLeft, {0, .8f, 2.5f, 2.5f }, {16, 192, 16, 16}, { 0, 0, 0, 0 }));
	
	// Energy GFX
	m_hud_elements.push_back(new UIElement(TopLeft, { 0, .6f,  2, 2 }, {64, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Hunger GFX
	m_hud_elements.push_back(new UIElement(TopRight, { .775f, .8f,  2, 2 }, {32, 192, 16, 16}, { 0, 0, 0, 0 }));

	// Thirst GFX
	m_hud_elements.push_back(new UIElement(TopRight, {-.775f, .8f,  2, 2 }, {48, 192, 16, 16}, { 0, 0, 0, 0 }));

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
	m_in_game_menu_elements.push_back(new SaveButton(TopLeft, { -.85f, .8f, 2.75f, 2.75f }, { 0, 240, 16, 16 }, { 0, 0, 0, 0 }));
	m_in_game_menu_elements.push_back(new MuteButton(TopLeft, { -.7f, .8f, 2.75f, 2.75f }, { 0, 256, 16, 16 }, { 0, 0, 0, 0 }));
	m_in_game_menu_elements.push_back(new SystemSettings(TopLeft, { -.55f, .8f, 2.75f, 2.75f }, { 0, 224, 16, 16 }, { 0, 0, 0, 0 }));


	// System panel

	m_syspanel_elements.push_back(new UIElement(TopRight, { 0, .8f, 4.5f, 4.5f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }));

	// System Options
	m_syspanel_elements.push_back(new DebugButton(TopLeft, { -0.075f, .8f, 2.75f, 2.75f }, { 0, 272, 16, 16 }, { 0, 0, 0, 0 }));
	m_syspanel_elements.push_back(new ReturnToMenuButton(TopLeft, { 0.075f, .8f, 2.75f, 2.75f }, { 0, 304, 16, 16 }, { 0, 0, 0, 0 }));

	// Debug

	m_debug_elements.push_back(new UIElement(TopLeft, { 0.075f, .8f, 2.75f, 2.75f }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }));


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
	for (int i = 0; i < m_main_menu_elements.size(); i++)
	{
		if (m_main_menu_elements[i] != nullptr)
		{
			if (!m_main_menu_elements[i]->IsInitialized())
			{
				m_main_menu_elements[i]->Start();
			}
		}
	}

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

	for (int i = 0; i < m_syspanel_elements.size(); i++)
	{
		if (m_syspanel_elements[i] != nullptr)
		{
			m_syspanel_elements[i]->Start();

		}
	}

	for (int i = 0; i < m_debug_elements.size(); i++)
	{
		if (m_debug_elements[i] != nullptr)
		{
			m_debug_elements[i]->Start();

		}
	}
}

void Canvas::RenderStart(SDL_Renderer* renderer)
{
	for (int i = 0; i < m_main_menu_elements.size(); i++)
	{
		if (m_main_menu_elements[i] != nullptr)
		{
			if (!m_main_menu_elements[i]->IsRenderInitialized())
			{
				m_main_menu_elements[i]->RenderStart(renderer);
			}
		}
	}

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

	for (int i = 0; i < m_syspanel_elements.size(); i++)
	{
		if (m_syspanel_elements[i] != nullptr)
		{
			m_syspanel_elements[i]->RenderStart(renderer);

		}
	}

	for (int i = 0; i < m_debug_elements.size(); i++)
	{
		if (m_debug_elements[i] != nullptr)
		{
			m_debug_elements[i]->RenderStart(renderer);

		}
	}
}

void Canvas::Update(Camera camera)
{
    // Do ui updates here

	switch (m_current_ui) 
	{
	case MainMenu:
		for (int i = 0; i < m_main_menu_elements.size(); i++)
		{
			if (m_main_menu_elements[i] != nullptr)
			{
				m_main_menu_elements[i]->Update(camera);
			}
		}
		break;
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

				SystemSettings* s = dynamic_cast<SystemSettings*>(m_in_game_menu_elements[i]);

				if (s != nullptr) 
				{
					if (s->Pressed()) 
					{
						m_current_ui = SystemMenu;
					}
				}
			}
		}

		if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			m_current_ui = HUD;
		}
		break;
	case SystemMenu:
		for (int i = 0; i < m_syspanel_elements.size(); i++)
		{
			if (m_syspanel_elements[i] != nullptr)
			{
				m_syspanel_elements[i]->Update(camera);

			}
		}

		if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			m_current_ui = InGameMenu;

			for (int i = 0; i < m_in_game_menu_elements.size(); i++)
			{
				if (m_in_game_menu_elements[i] != nullptr)
				{
					SystemSettings* s = dynamic_cast<SystemSettings*>(m_in_game_menu_elements[i]);

					if (s != nullptr)
					{
						s->SetPressed(false);
					}
				}
			}
		}
		break;
	}

	if (Game::DebugMode()) 
	{
		for (int i = 0; i < m_debug_elements.size(); i++)
		{
			if (m_debug_elements[i] != nullptr)
			{
				m_debug_elements[i]->Update(camera);

			}
		}

		if (m_debug_elements.size() > 0) 
		{
			m_debug_elements[0]->SetText(to_string((int)(1 / Time::GetDeltaTime())));
		}
	}
}

void Canvas::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
    // Do Render Here

	switch (m_current_ui)
	{
	case MainMenu:
		for (int i = 0; i < m_main_menu_elements.size(); i++)
		{
			if (m_main_menu_elements[i] != nullptr)
			{
				m_main_menu_elements[i]->RenderUpdate(renderer, camera);
			}
		}
		break;
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
	case SystemMenu:
		for (int i = 0; i < m_syspanel_elements.size(); i++)
		{
			if (m_syspanel_elements[i] != nullptr)
			{
				m_syspanel_elements[i]->RenderUpdate(renderer, camera);
			}
		}
		break;
	}

	if (Game::DebugMode())
	{
		for (int i = 0; i < m_debug_elements.size(); i++)
		{
			if (m_debug_elements[i] != nullptr)
			{
				m_debug_elements[i]->RenderUpdate(renderer, camera);
			}
		}
	}
}

void Canvas::InitializePlayerHUD(Player* player)
{
	if (player == nullptr)
	{
		cout << "No player" << endl;

		return;
	}

	player->InitializeHUD(m_sliders);
}