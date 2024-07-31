#include "Collectable.h"

#include "Player.h"

Collectable::Collectable()
	: Collectable({ 0,0,1,1 })
{
	m_collider_scale = { .25f,.25f };
	m_image_name = "Collectables";

	if (m_key) m_sprite_info = m_gfx_info;
}

Collectable::Collectable(Transform transform, bool isKey)
{
	m_transform = transform;
	m_collider.SetTrigger(true);
	m_collider_scale = { .25f,.25f };
	m_image_name = "Collectables";

	m_key = isKey;

	if (m_key) m_sprite_info = m_gfx_info;
}

Collectable::~Collectable()
{
}

void Collectable::Update(float deltaTime)
{
	if (m_frame_collided.size() > 0)
	{
		CollisionResponse();
	}

	GameObject::Update(deltaTime);
}

void Collectable::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_sprite_info);

	GameObject::RenderStart(renderer, camera);
}

void Collectable::CollisionResponse()
{
	for (int i = 0; i < m_frame_collided.size(); i++)
	{
		Player* player = dynamic_cast<Player*>(m_frame_collided[i].gameObject);

		if (player != nullptr)
		{
			if (player->AddCollectable(*this))
			{
				AudioManager::PlayEffect("collectable");
				Delete();
			}
		}
	}
}
