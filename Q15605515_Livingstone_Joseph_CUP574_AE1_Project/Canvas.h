#pragma once

#include "Structs.h"
#include "Input.h"

#include "UIElement.h"
#include "Button.h"
#include "MuteButton.h"
#include "MuteEffectButton.h"
#include "SettingsButton.h"
#include "SystemSettings.h"
#include "DebugButton.h"
#include "ReturnToMenuButton.h"
#include "PlayButton.h"
#include "QuitButton.h"
#include "HowToPlayButton.h"
#include "LevelSelectButton.h"
#include "Slider.h"

class Player;
class Camera;

enum CurrentUI {
	MainMenu, LevelSelect, HowToPlay, HUD, InGameMenu, SystemMenu, VictoryScreen, DeathScreen
};

class Canvas
{ 
public:

	Canvas();

	~Canvas();

	void Start();

	void RenderStart(SDL_Renderer* renderer);

	void Update(Camera camera);

	void RenderUpdate(SDL_Renderer* renderer, Camera camera);

	void InitializePlayerHUD(Player* player);

	void ChangeState(CurrentUI state) { m_current_ui = state; }
	CurrentUI GetState() { return m_current_ui; }

private:

	CurrentUI m_current_ui{ HUD };
	
	vector<UIElement*> m_main_menu_elements;

	vector<UIElement*> m_level_select_elements;

	vector<UIElement*> m_controls_menu_elements;

	vector<UIElement*> m_hud_elements;

	vector<UIElement*> m_in_game_menu_elements;

	vector<Slider*> m_sliders;

	UIElement* m_score_ui{ nullptr };

	vector<UIElement*> m_high_score_elements;

	vector<UIElement*> m_syspanel_elements;

	vector<UIElement*> m_victory_elements;
	vector<UIElement*> m_death_elements;

	vector<UIElement*> m_debug_elements;
};