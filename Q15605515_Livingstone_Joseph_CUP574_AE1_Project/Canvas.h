#pragma once

#include "Structs.h"
#include "Input.h"

#include "UIElement.h"
#include "Button.h"
#include "MuteButton.h"
#include "SaveButton.h"
#include "SettingsButton.h"
#include "SystemSettings.h"
#include "Slider.h"

class Player;
class Camera;

enum CurrentUI {
	MainMenu, HUD, InGameMenu
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

private:

	CurrentUI m_current_ui{ HUD };
	
	vector<UIElement*> m_hud_elements;

	vector<UIElement*> m_in_game_menu_elements;

	vector<Slider*> m_sliders;

};