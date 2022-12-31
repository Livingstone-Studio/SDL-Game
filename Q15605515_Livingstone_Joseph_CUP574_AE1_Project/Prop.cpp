#include "Prop.h"

#include "Game.h"
#include "ScoreManager.h"

#include "Player.h"

Prop::Prop()
{
	m_end_tile = false;

	if (m_end_tile) m_collider.SetTrigger(true);
}

Prop::Prop(Transform transform, string name, float sortOrder, AnimationInfo s, bool collision, bool dynamicSort, Vector2 scaleFactor, bool endTile)
	: m_sprite_info{ s }
{
	m_transform = transform;
	m_image_name = name;
	m_default_sort = sortOrder;
	m_dynamic_sort_order = dynamicSort;

	m_collider.SetActive(collision);
	m_collider_scale = scaleFactor;

	m_end_tile = endTile;

	if (m_end_tile) m_collider.SetTrigger(true);
}

Prop::Prop(Transform transform, TileInfo tileInfo, bool collision, Vector2 scaleFactor, bool endTile)
	: Prop(transform, tileInfo.name, tileInfo.sortOrder, tileInfo.animInfo, collision, tileInfo.dynamicSort, scaleFactor)
{
	m_end_tile = endTile;

	if (m_end_tile) m_collider.SetTrigger(true);
}

Prop::~Prop()
{
}

void Prop::Update(float deltaTime)
{
	if (m_frame_collided.size() > 0 && ScoreManager::IsKeyActivate())
	{
		CollisionResponse();
	}

	GameObject::Update(deltaTime);
}

void Prop::CollisionResponse()
{ 
	if (m_end_tile) 
	{
		for (int i = 0; i < m_frame_collided.size(); i++)
		{
			if (m_frame_collided[i].info.trigger || m_frame_collided[i].gameObject->GetCollider().IsTrigger())
			{
				Player* player = dynamic_cast<Player*>(m_frame_collided[i].gameObject);

				if (player != nullptr)
				{
					Game::ChangeCanvasState(VictoryScreen);
				}
			}
		}
	}
}

void Prop::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_sprite_info);

	GameObject::RenderStart(renderer, camera);
}
