#pragma once

#include "Enemy.h"

class Slime : public Enemy
{
public:

	Slime();
	Slime(Vector2 position);
	Slime(Transform transform);

	virtual void Attack() override;

	virtual void RenderStart(SDL_Renderer* renderer, Camera camera);

protected:

	string m_image_name{ "Slime" };

	CharacterAnimInfo m_charAnimInfo{ m_image_name,
		//Idle
		{ "idleR", {1,1,0,0,true}, {1,1,0,4,true}},
		{ "idleL", {2,1,0,0,true}, {2,1,0,4,true} },
		{ "idleTR", {3,1,0,0,true}, {3,1,0,4,true} },
		{ "idleTL", {4,1,0,0,true}, {4,1,0,4,true} },

		//Move
		{ "moveR", {9,4,0.1f,0,true}, {9,4,0.1f,4,true} },
		{ "moveL", {10,4,0.1f,0,true}, {10,4,0.1f,4,true} },
		{ "moveTR", {11,4,0.1f,0,true}, {11,4,0.1f,4,true} },
		{ "moveTL", {12,4,0.1f,0,true}, {12,4,0.1f,4,true} },

		//Attack
		{ "attackR", {0,4,0.05f,0,false}, {0,4,0.05f,4,false} },
		{ "attackL", {1,4,0.05f,0,false}, {1,4,0.05f,4,false} },
		{ "attackTR", {2,4,0.05f,0,false}, {2,4,0.05f,4,false} },
		{ "attackTL", {3,4,0.05f,0,false}, {3,4,0.05f,4,false} },

		//Hit + Death
		{ "hitR", {5,4,0.15f,0,false}, {5,4,0.15f,4,false} },
		{ "hitL", {6,4,0.15f,0,false}, {6,4,0.15f,4,false} },
		{ "hitTR", {7,4,0.15f,0,false}, {7,4,0.15f,4,false} },
		{ "hitTL", {8,4,0.15f,0,false}, {8,4,0.15f,4,false} },
		{ "deathFR", {0,13,0.15f,0,false}, {13,13,0.15f,0,false} }
	};

};

