#pragma once

#include "Enemy.h"

class Orc : public Enemy
{
public:

	Orc();
	Orc(Vector2 position);
	Orc(Transform transform);

protected:
	
	string m_image_name{ "Orc" };

	CharacterAnimInfo m_charAnimInfo{ m_image_name,
		//Idle
		{ "idleR", {20,1,0,0,true}, {20,1,0,4,true}},
		{ "idleL", {21,1,0,0,true}, {21,1,0,4,true} },
		{ "idleTR", {22,1,0,0,true}, {22,1,0,4,true} },
		{ "idleTL", {23,1,0,0,true}, {23,1,0,4,true} },

		//Move
		{ "moveR", {20,4,0.1f,0,true,0,2}, {20,4,0.1f,4,true} },
		{ "moveL", {21,4,0.1f,0,true,0,2}, {21,4,0.1f,4,true} },
		{ "moveTR", {22,4,0.1f,0,true,0,2}, {22,4,0.1f,4,true} },
		{ "moveTL", {23,4,0.1f,0,true,0,2}, {23,4,0.1f,4,true} },

		//Attack
		{ "attackR", {0,4,0.09f,0,false,2}, {0,4,0.09f,4,false} },
		{ "attackL", {1,4,0.09f,0,false,2}, {1,4,0.09f,4,false} },
		{ "attackTR", {2,4,0.09f,0,false,2}, {2,4,0.09f,4,false} },
		{ "attackTL", {3,4,0.09f,0,false,2}, {3,4,0.09f,4,false} },

		//Hit + Death
		{ "hitR", {8,4,0.15f,0,false}, {8,4,0.15f,4,false} },
		{ "hitL", {9,4,0.15f,0,false}, {9,4,0.15f,4,false} },
		{ "hitTR", {10,4,0.15f,0,false}, {10,4,0.15f,4,false} },
		{ "hitTL", {11,4,0.15f,0,false}, {11,4,0.15f,4,false} },
		{ "deathFR", {7,13,0.15f,0,false}, {16,13,0.15f,4,false} }
	};
};
