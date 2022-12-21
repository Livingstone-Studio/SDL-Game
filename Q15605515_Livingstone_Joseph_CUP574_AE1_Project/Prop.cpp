#include "Prop.h"

Prop::Prop()
{
}

Prop::Prop(Transform transform, string name, float sortOrder, AnimationInfo s, bool collision, bool dynamicSort, Vector2 scaleFactor)
	: m_sprite_info{ s }
{
	m_transform = transform;
	m_image_name = name;
	m_default_sort = sortOrder;
	m_dynamic_sort_order = dynamicSort;

	m_collider.SetActive(collision);
	m_collider_scale = scaleFactor;
}

Prop::Prop(Transform transform, TileInfo tileInfo, bool collision, Vector2 scaleFactor)
	: Prop(transform, tileInfo.name, tileInfo.sortOrder, tileInfo.animInfo, collision, tileInfo.dynamicSort, scaleFactor)
{
}

Prop::~Prop()
{
}

void Prop::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_image_name, m_sprite_info);

	GameObject::RenderStart(renderer, camera);
}
