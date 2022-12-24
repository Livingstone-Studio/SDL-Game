#pragma once

#include "GameObject.h"

enum CollectableType {
	PotatoSeeds, Potato, CauliSeeds, Cauli
};

class Collectable : public GameObject
{
public:

	Collectable();
	Collectable(Transform transform, CollectableType collectable_type);
	
	~Collectable();

	virtual void Update(float deltaTime) override;

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera);

	virtual void CollisionResponse();

protected:

	string m_image_name{ "Collectables" };

	AnimationInfo m_sprite_info{ "potato", {0, 1, 0.0f, 14, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };

	AnimationInfo m_potato_info{ "potato", {0, 1, 0.0f, 14, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };
	AnimationInfo m_potato_seeds_info{ "potatoSeeds", {0, 1, 0.0f, 10, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };

	AnimationInfo m_cauli_info{ "cauli", {3, 1, 0.0f, 14, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };
	AnimationInfo m_cauli_seeds_info{ "cauliSeeds", {3, 1, 0.0f, 10, false}, {-5, 0, 0.0f, 0, false}, { 0, 0 } };

};