#include "Player.h"

Player::Player()
{

}

Player::Player(Vector2 position)
{
	m_transform.position = position;

}

Player::Player(Transform transform)
{
	m_transform = transform;
}

Player::~Player()
{
}

void Player::RenderStart(SDL_Renderer* renderer, Camera camera)
{
    m_gfx.InitAnim(renderer, m_sprite_name, m_charAnimInfo.idleR);

    GameObject::RenderStart(renderer, camera);
}

void Player::InputUpdate(float deltaTime)
{
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

    SetMovementDirection(moveVector.Normalized());
}
