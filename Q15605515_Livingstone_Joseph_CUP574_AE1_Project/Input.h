#pragma once

#include <SDL.h>

#include "Structs.h"

static class Input
{
public:

	static void Initialize();

	static bool EventHandler();

	static bool GetKey(SDL_Scancode key);

	static bool GetKeyDown(SDL_Scancode key);

	static bool GetKeyUp(SDL_Scancode key);

	static void Update();

	static void Cleanup();

	static Vector2 GetMousePosition();

	static bool LeftMousePress() { return m_left_mouse_press_frame; }

private:

	static const Uint8* m_keyboardState;
	static const Uint8* m_previousKeyboardState;

	static bool m_left_mouse_press_frame;

};
