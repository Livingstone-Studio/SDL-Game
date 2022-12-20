#include "GameObject.h"

GameObject::GameObject()
	: m_transform()
{
}

GameObject::GameObject(Vector2 position)
	: m_transform( position )
{
}

GameObject::GameObject(Transform transform)
	: m_transform( transform )
{
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
	m_sort_order = m_default_sort - m_transform.position.y;

	m_initialized = true; 
}

void GameObject::Update(float deltaTime)
{
	if (m_initialized && !m_deletion) m_gfx.Update();

	if (m_dynamic_sort_order) m_sort_order = m_default_sort - m_transform.position.y;
}

void GameObject::RenderStart(SDL_Renderer* renderer, Camera camera)
{
	m_render_initialized = true;
}

void GameObject::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion)
	{
		m_gfx.RenderUpdate(renderer, camera.ConvertedToScreenSpace(AnimOffsetPosition()));
	}
}

Transform GameObject::AnimOffsetPosition()
{
	Transform t = m_transform;
	Vector2 o = m_gfx.GetOffset();

	t.position += o;

	return t;
}
