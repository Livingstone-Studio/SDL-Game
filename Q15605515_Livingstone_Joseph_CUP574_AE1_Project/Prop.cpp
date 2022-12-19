#include "Prop.h"

Prop::Prop()
{
}

Prop::Prop(Transform transform, string name, float sortOrder, AnimationInfo s, bool dynamicSort)
	: m_sprite_info{ s }
{
	m_transform = transform;
	m_sprite_name = name;
	m_default_sort = sortOrder;
	m_dynamic_sort_order = dynamicSort;
}

Prop::~Prop()
{
}

void Prop::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_gfx.InitAnim(renderer, m_sprite_name, m_sprite_info);

	GameObject::RenderStart(renderer, camera);
}
