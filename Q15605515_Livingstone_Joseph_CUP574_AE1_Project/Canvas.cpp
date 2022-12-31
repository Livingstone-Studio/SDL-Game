#include "Canvas.h"

#include "Camera.h"
#include "Player.h"
#include "ScoreManager.h"

#include "Game.h"

Canvas::Canvas()
{
	// Main Menu

	m_main_menu_elements.push_back(new UIElement(TopLeft, { 0, .8f, 5.0f, 5.0f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }, "Gobbie The Gobbo", { 8,2 }));
	m_main_menu_elements.push_back(new LevelSelectButton(TopLeft, { 0, -.2f, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }, this, { 4,.75f }));
	m_main_menu_elements.push_back(new HowToPlayButton(TopLeft, { 0, -.5f, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }, this, { 4,.75f }));
	m_main_menu_elements.push_back(new QuitButton(TopLeft, { 0, -.8f, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }));
	
	// Level Select

	m_level_select_elements.push_back(new UIElement(TopLeft, { -.5f, 0, 5.0f, 5.0f }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, "0", { 6,2 }, { 0,-.25f }));
	m_level_select_elements.push_back(new UIElement(TopLeft, { .5f, 0, 5.0f, 5.0f }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, "0", { 6,2 }, { 0,-.25f }));

	m_high_score_elements.push_back(m_level_select_elements[0]);
	m_high_score_elements.push_back(m_level_select_elements[1]);

	m_level_select_elements.push_back(new UIElement(TopLeft, { 0, .8f, 5.0f, 5.0f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }, "Press Escape To Return", { 6,1 }));
	
	m_level_select_elements.push_back(new PlayButton(TopLeft, { -.5f, 0, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }));
	m_level_select_elements.push_back(new PlayButton(TopLeft, { .5f, 0, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }));
	
	// How To Play

	m_controls_menu_elements.push_back(new UIElement(TopLeft, { 0, .8f, 5.0f, 5.0f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }, "Press Escape To Return", { 6,1 }));
	
	m_controls_menu_elements.push_back(new UIElement(TopLeft, { -.5f, 0, 5.0f, 5.0f }, { 81, 208, 23, 18 }, { 0, 0, 0, 0 }, "Move", { 6,2 }, { 0,-.5f }));
	m_controls_menu_elements.push_back(new UIElement(TopLeft, { .5f, 0, 4.0f, 4.0f }, { 113, 227, 7, 10 }, { 0, 0, 0, 0 }, "Attack", { 6,2 }, { 0,-.5f }));


	// HUD

	// Score

	m_hud_elements.push_back(new UIElement(TopLeft, { 0, -.8f, 7, 7 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, "0", { 2,1.5f }));

	m_score_ui = m_hud_elements[0];

	// Health GFX
	m_hud_elements.push_back(new Slider(TopLeft, { 0, .8f, 7, 7 }, { 192, 80, 48, 16 }, { 256, 16, 48, 16 }));
	m_hud_elements.push_back(new Slider(TopLeft, { 0, .6f, 5, 5 }, { 192, 80, 48, 16 }, { 464, 16, 48, 16 }));
	
	for (int i = 1; i < m_hud_elements.size(); i++)
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
	
	// In Game Menu

	// Panels

	m_in_game_menu_elements.push_back(new UIElement(TopLeft, { -.6975f, .8f, 4.5f, 4.5f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }));

	// Icons
	m_in_game_menu_elements.push_back(new MuteMusicButton(TopLeft, { -.85f, .8f, 2.75f, 2.75f }, { 0, 256, 16, 16 }, { 0, 0, 0, 0 }));
	m_in_game_menu_elements.push_back(new MuteEffectButton(TopLeft, { -.7f, .8f, 2.75f, 2.75f }, { 64, 256, 16, 16 }, { 0, 0, 0, 0 }));
	m_in_game_menu_elements.push_back(new SystemSettings(TopLeft, { -.55f, .8f, 2.75f, 2.75f }, { 0, 224, 16, 16 }, { 0, 0, 0, 0 }));


	// System panel

	m_syspanel_elements.push_back(new UIElement(TopRight, { 0, .8f, 4.5f, 4.5f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }));

	// System Options
	m_syspanel_elements.push_back(new DebugButton(TopLeft, { -0.075f, .8f, 2.75f, 2.75f }, { 0, 272, 16, 16 }, { 0, 0, 0, 0 }));
	m_syspanel_elements.push_back(new ReturnToMenuButton(TopLeft, { 0.075f, .8f, 2.75f, 2.75f }, { 0, 304, 16, 16 }, { 0, 0, 0, 0 }));

	// Victory Screen

	m_victory_elements.push_back(new UIElement(TopLeft, { 0, .8f, 5.0f, 5.0f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }, "Victory", { 8,2 }));
	m_victory_elements.push_back(new ReturnToMenuButton(TopLeft, { 0, -.2f, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }));

	// Death Screen

	m_death_elements.push_back(new UIElement(TopLeft, { 0, .8f, 5.0f, 5.0f }, { 16, 288, 48, 16 }, { 0, 0, 0, 0 }, "You Lose", { 8,2 }));
	m_death_elements.push_back(new ReturnToMenuButton(TopLeft, { 0, -.2f, 4.0f, 4.0f }, { 64, 240, 48, 16 }, { 0, 0, 0, 0 }));

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

	for (int i = 0; i < m_level_select_elements.size(); i++)
	{
		if (m_level_select_elements[i] != nullptr)
		{
			if (!m_level_select_elements[i]->IsInitialized())
			{
				m_level_select_elements[i]->Start();
			}
		}
	}

	for (int i = 0; i < m_controls_menu_elements.size(); i++)
	{
		if (m_controls_menu_elements[i] != nullptr)
		{
			if (!m_controls_menu_elements[i]->IsInitialized())
			{
				m_controls_menu_elements[i]->Start();
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

	for (int i = 0; i < m_victory_elements.size(); i++)
	{
		if (m_victory_elements[i] != nullptr)
		{
			if (!m_victory_elements[i]->IsInitialized())
			{
				m_victory_elements[i]->Start();
			}
		}
	}

	for (int i = 0; i < m_death_elements.size(); i++)
	{
		if (m_death_elements[i] != nullptr)
		{
			if (!m_death_elements[i]->IsInitialized())
			{
				m_death_elements[i]->Start();
			}
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

	for (int i = 0; i < m_level_select_elements.size(); i++)
	{
		if (m_level_select_elements[i] != nullptr)
		{
			if (!m_level_select_elements[i]->IsRenderInitialized())
			{
				m_level_select_elements[i]->RenderStart(renderer);
			}
		}
	}

	for (int i = 0; i < m_controls_menu_elements.size(); i++)
	{
		if (m_controls_menu_elements[i] != nullptr)
		{
			if (!m_controls_menu_elements[i]->IsRenderInitialized())
			{
				m_controls_menu_elements[i]->RenderStart(renderer);
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

	for (int i = 0; i < m_victory_elements.size(); i++)
	{
		if (m_victory_elements[i] != nullptr)
		{
			if (!m_victory_elements[i]->IsRenderInitialized())
			{
				m_victory_elements[i]->RenderStart(renderer);
			}
		}
	}

	for (int i = 0; i < m_death_elements.size(); i++)
	{
		if (m_death_elements[i] != nullptr)
		{
			if (!m_death_elements[i]->IsRenderInitialized())
			{
				m_death_elements[i]->RenderStart(renderer);
			}
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
	case HowToPlay:
		for (int i = 0; i < m_controls_menu_elements.size(); i++)
		{
			if (m_controls_menu_elements[i] != nullptr)
			{
				m_controls_menu_elements[i]->Update(camera);
			}
		}

		if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			m_current_ui = InGameMenu;
		}
		break;
	case LevelSelect:
		for (int i = 0; i < m_level_select_elements.size(); i++)
		{
			if (m_level_select_elements[i] != nullptr)
			{
				m_level_select_elements[i]->Update(camera);
			}
		}

		m_high_score_elements[0]->SetText("Highscore: " + to_string(ScoreManager::GetHighScoreOne()));
		m_high_score_elements[1]->SetText("Highscore: " + to_string(ScoreManager::GetHighScoreTwo()));

		if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			m_current_ui = InGameMenu;
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
	case VictoryScreen:
		for (int i = 0; i < m_victory_elements.size(); i++)
		{
			if (m_victory_elements[i] != nullptr)
			{
				m_victory_elements[i]->Update(camera);
			}
		}
		break;
	case DeathScreen:
		for (int i = 0; i < m_death_elements.size(); i++)
		{
			if (m_death_elements[i] != nullptr)
			{
				m_death_elements[i]->Update(camera);
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
	case HowToPlay:
		for (int i = 0; i < m_controls_menu_elements.size(); i++)
		{
			if (m_controls_menu_elements[i] != nullptr)
			{
				m_controls_menu_elements[i]->RenderUpdate(renderer, camera);
			}
		}
		break;
	case LevelSelect:
		for (int i = 0; i < m_level_select_elements.size(); i++)
		{
			if (m_level_select_elements[i] != nullptr)
			{
				m_level_select_elements[i]->RenderUpdate(renderer, camera);
			}
		}

		if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			m_current_ui = InGameMenu;
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
	case VictoryScreen:
		for (int i = 0; i < m_victory_elements.size(); i++)
		{
			if (m_victory_elements[i] != nullptr)
			{
				m_victory_elements[i]->RenderUpdate(renderer, camera);
			}
		}
		break;
	case DeathScreen:
		for (int i = 0; i < m_death_elements.size(); i++)
		{
			if (m_death_elements[i] != nullptr)
			{
				m_death_elements[i]->RenderUpdate(renderer, camera);
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

	player->InitializeHUD(m_sliders, m_score_ui);
}