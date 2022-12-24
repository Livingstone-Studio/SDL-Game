#include "Collectable.h"

#include "Player.h"

Collectable::Collectable()
	: Collectable({ 0,0,1,1 }, Potato)
{
	m_collider_scale = { .25f,.25f };
	m_image_name = "Collectables";
}

Collectable::Collectable(Transform transform, CollectableType collectable_type)
{
	m_transform = transform;
	m_collider.SetTrigger(true);
	m_collider_scale = { .25f,.25f };
	m_image_name = "Collectables";

	switch (collectable_type) 
	{
	case PotatoSeeds:
		m_sprite_info = m_potato_seeds_info;
		break;
	case Potato:
		m_sprite_info = m_potato_info;
		break;
	case CauliSeeds:
		m_sprite_info = m_cauli_seeds_info;
		break;
	case Cauli:
		m_sprite_info = m_cauli_info;
		break;
	}
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
			if (player->AddToInventory(*this))
			{
				AudioManager::PlayEffect("collectable");
				Delete();
			}
		}
	}
}
