#include "Player.h"

Player::Player()
{
    m_move_speed = 5.0f;
}

Player::Player(Vector2 position)
{
	m_transform.position = position;
    m_move_speed = 5.0f;

}

Player::Player(Transform transform)
{
	m_transform = transform;
    m_move_speed = 5.0f;
}

Player::~Player()
{
}

void Player::RenderStart(SDL_Renderer* renderer, Camera camera)
{
    m_gfx.InitAnim(renderer, m_image_name, m_char_anim_info.idleR);

    GameObject::RenderStart(renderer, camera);
}

void Player::InputUpdate(float deltaTime)
{
    if (m_death) return;
    Vector2 moveVector;

    if (Input::GetKey(SDL_SCANCODE_W))
    {
        moveVector.y = 1;
    }
    if (Input::GetKey(SDL_SCANCODE_S))
    {
        moveVector.y = -1;
    }
    if (Input::GetKey(SDL_SCANCODE_A))
    {
        moveVector.x = -1;
    }
    if (Input::GetKey(SDL_SCANCODE_D))
    {
        moveVector.x = 1;
    }

    if (Input::GetKeyDown(SDL_SCANCODE_E))
    {
        Attack();
    }

    SetMovementDirection(moveVector);
}
