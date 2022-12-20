#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

Transform Camera::ConvertedToScreenSpace(Transform t)
{
	Vector2 offset;

	m_transform.scale = m_units_on_screen * m_scale;

	// Get object offset from cam
	offset = t.position - m_transform.position;

	// Camera Range (r-l, top-bottom)
	Vector2 range = { m_transform.scale.x - (-m_transform.scale.x), m_transform.scale.y - (-m_transform.scale.y) };

	// Get The Normalized Value To Scale To Fit Current Resolution.

	Vector2 resolutionScale = m_window_size / m_default_window_size;

	// Shift so object position min = 0;
	offset.x = offset.x - (-m_transform.scale.x * resolutionScale.x);
	offset.y = offset.y - (-m_transform.scale.y * resolutionScale.y);

	// Normalise the offset.
	offset.x = offset.x / (range.x);
	offset.y = offset.y / (range.y);

	offset.x = offset.x / (resolutionScale.x);
	offset.y = offset.y / (resolutionScale.y);

	// Apply Normalised To Screen.

	return { { (m_window_size.x * offset.x), (m_window_size.y - (m_window_size.y * offset.y))}, t.scale / m_scale };
}

void Camera::Follow(GameObject* target, float deltaTime)
{
	Vector2 moveVector = target->GetTransform().position - m_transform.position;

	if (moveVector.Magnitude() > m_distance_before_follow) 
	{
		SetClampedSpeed(moveVector.Magnitude());

		moveVector = moveVector.Normalized() * m_follow_speed * deltaTime;

		m_transform.position += moveVector;
	}
}

void Camera::Update( Vector2 defaultCamSize, Vector2 currentCamSize)
{
	m_default_window_size = defaultCamSize;
	m_window_size = currentCamSize;

	if (Input::GetKeyDown(SDL_SCANCODE_1))
	{
		SetScale(1);
	}
	if (Input::GetKeyDown(SDL_SCANCODE_2))
	{
		SetScale(2);
	}
	if (Input::GetKeyDown(SDL_SCANCODE_3))
	{
		SetScale(3);
	}
	if (Input::GetKeyDown(SDL_SCANCODE_4))
	{
		SetScale(4);
	}

}

void Camera::RenderStart(SDL_Renderer* renderer, vector<GameObject*> gameObjects)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] != nullptr)
		{
			if (!gameObjects[i]->IsRenderInitialized())	gameObjects[i]->RenderStart(renderer, *this);
		}
	}
}

void Camera::RenderUpdate(SDL_Renderer* renderer, vector<GameObject*> gameObjects)
{
	vector<GameObject*> sorted = SortRenderOrder(gameObjects);

	for (int i = 0; i < sorted.size(); i++) 
	{
		if (sorted[i] != nullptr) 
		{
			sorted[i]->RenderUpdate(renderer, *this);
		}
	}
}

vector<GameObject*> Camera::SortRenderOrder(vector<GameObject*> gameObjects)
{
	stable_sort(gameObjects.begin(), gameObjects.end(),
		[](GameObject* g1, GameObject* g2) {
			return g1->m_sort_order < g2->m_sort_order; });

	return gameObjects;
}

void Camera::SetClampedSpeed(float s)
{
	if (s < m_min_clamped_speed) s = m_min_clamped_speed;
	else if (s > m_max_clamped_speed) s = m_max_clamped_speed;

	m_follow_speed = s;
}
