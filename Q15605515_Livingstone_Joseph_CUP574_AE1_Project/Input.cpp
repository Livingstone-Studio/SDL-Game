#include "Input.h"

const Uint8* Input::m_keyboardState;
const Uint8* Input::m_previousKeyboardState;

bool Input::m_left_mouse_press_frame;

void Input::Initialize()
{
    m_keyboardState = SDL_GetKeyboardState(NULL);
    m_previousKeyboardState = (Uint8*)malloc(SDL_NUM_SCANCODES);
}

bool Input::EventHandler()
{
    SDL_Event m_event;

    while (SDL_PollEvent(&m_event))
    {
        switch (m_event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if (m_event.type == SDL_MOUSEBUTTONDOWN && m_event.button.button == SDL_BUTTON_LEFT)
            {
                m_left_mouse_press_frame = true;
            }
            break;
        case SDL_QUIT:
            return false;
            break;
        }
    }

    return true;
}

bool Input::GetKey(SDL_Scancode key)
{
    return m_keyboardState[key];
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return m_keyboardState[key] && !(m_previousKeyboardState[key]);
}

bool Input::GetKeyUp(SDL_Scancode key)
{
    return !(m_keyboardState[key]) && m_previousKeyboardState[key];
}

void Input::Update()
{
    m_left_mouse_press_frame = false;

    SDL_memcpy((void*)m_previousKeyboardState, m_keyboardState, SDL_NUM_SCANCODES);
}

void Input::Cleanup()
{
    free((void*)m_previousKeyboardState);
}

Vector2 Input::GetMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    return { (float)x,(float)y };
}
