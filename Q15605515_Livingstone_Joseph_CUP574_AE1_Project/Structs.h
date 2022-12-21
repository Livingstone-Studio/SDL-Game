#pragma once

#include <string>

class GameObject;

struct Vector2
{
public:

	float x{ 0 };
	float y{ 0 };

	Vector2()
		: x{ 0 }, y{ 0 }
	{

	};

	Vector2(float X, float Y)
		: x{ X }, y{ Y }
	{

	};

	float Magnitude()
	{
		float i = (x * x) + (y * y);

		if (i == 0) return 0;
		else return sqrt(i);
	}

	Vector2 Normalized()
	{
		float mag = Magnitude();

		if ((x == 0 && y == 0) || mag == 0) return { 0, 0 };
		else if (x == 0 && y != 0) return { 0, y / mag };
		else if (x != 0 && y == 0) return { x / mag, 0 };
		else return { x / mag, y / mag };
	}

	Vector2 operator + (Vector2& vec)
	{
		Vector2 r;

		r.x = this->x + vec.x;
		r.y = this->y + vec.y;

		return r;
	}

	Vector2 operator - (Vector2& vec)
	{
		Vector2 r;

		r.x = this->x - vec.x;
		r.y = this->y - vec.y;

		return r;
	}

	Vector2 operator * (Vector2& vec)
	{
		Vector2 r;

		r.x = this->x * vec.x;
		r.y = this->y * vec.y;

		return r;
	}

	Vector2 operator / (Vector2& vec)
	{
		Vector2 r;

		r.x = this->x / vec.x;
		r.y = this->y / vec.y;

		return r;
	}

	Vector2 operator += (Vector2& vec) 
	{
		this->x += vec.x;
		this->y += vec.y;

		return *this;
	}

	Vector2 operator -= (Vector2& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;

		return *this;
	}

	Vector2 operator *= (Vector2& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;

		return *this;
	}

	Vector2 operator /= (Vector2& vec)
	{
		this->x /= vec.x;
		this->y /= vec.y;

		return *this;
	}

	Vector2 operator * (float value)
	{
		Vector2 r;

		r.x = this->x * value;
		r.y = this->y * value;

		return r;
	}

	Vector2 operator / (float value)
	{
		Vector2 r;

		r.x = this->x / value;
		r.y = this->y / value;

		return r;
	}

	Vector2 operator *= (float value)
	{
		this->x *= value;
		this->y *= value;

		return *this;
	}

	Vector2 operator /= (float value)
	{
		this->x /= value;
		this->y /= value;

		return *this;
	}
};

struct Transform
{
public:

	Transform()
	{
		position.x = 0;
		position.y = 0;

		scale.x = 1;
		scale.y = 1;
	}

	Transform(float x, float y)
	{
		position.x = x;
		position.y = y;

		scale.x = 1;
		scale.y = 1;
	}

	Transform(Vector2 pos) 
	{
		position = pos;

		scale.x = 1;
		scale.y = 1;
	}

	Transform(Vector2 pos, Vector2 sca)
	{
		position = pos;
		scale = sca;
	}

	Transform(float x, float y, float xScale, float yScale)
	{
		position.x = x;
		position.y = y;

		scale.x = xScale;
		scale.y = yScale;
	}

	Vector2 position;
	Vector2 scale;
};

struct AnimClipInfo
{
public:

	int row{ 0 };
	int spriteCount{ 0 };
	float animTimeBetween{ 1.0f };
	int start{ 0 };
	bool looping{ true };
	int eventFrame{ -1 };

	AnimClipInfo()
		: AnimClipInfo(0, 0, 1.0f, 0, true, -1)
	{
	}

	AnimClipInfo(int r, int sC, float t, int s, bool l, int e = -1)
		: row{ r }, spriteCount{ sC }, animTimeBetween{ t }, start{ s }, looping{ l }, eventFrame{ e }
	{
	}

};

struct AnimationInfo 
{
public:

	std::string name{ "" };

	AnimClipInfo actionAnimClip;
	AnimClipInfo actionAnimShadow;

	Vector2 offset{ 0,0 };

	int eventTrigger{ -1 };

	AnimationInfo() 
	{
	}

	AnimationInfo(std::string n, AnimClipInfo action, AnimClipInfo shadow, Vector2 o = { 0,0 }, int e = -1)
		: name{ n }, actionAnimClip { action }, actionAnimShadow{ shadow }, offset{ o }, eventTrigger{ e }
	{
	}

};

struct CharacterAnimInfo 
{
public:

	std::string path{ "" };

	// Idle
	AnimationInfo idleR;
	AnimationInfo idleL;
	AnimationInfo idleTR;
	AnimationInfo idleTL;

	// Move
	AnimationInfo moveR;
	AnimationInfo moveL;
	AnimationInfo moveTR;
	AnimationInfo moveTL;

	// Attack
	AnimationInfo attackR;
	AnimationInfo attackL;
	AnimationInfo attackTR;
	AnimationInfo attackTL;

	// Hit
	AnimationInfo hitR;
	AnimationInfo hitL;
	AnimationInfo hitTR;
	AnimationInfo hitTL;

	// Die
	AnimationInfo death;

	CharacterAnimInfo() 
	{

	}

	CharacterAnimInfo(std::string path, AnimationInfo idleFR, AnimationInfo idleFL, AnimationInfo idleFTR, AnimationInfo idleFTL,
		AnimationInfo moveFR, AnimationInfo moveFL, AnimationInfo moveFTR, AnimationInfo moveFTL,
		AnimationInfo attackFR, AnimationInfo attackFL, AnimationInfo attackFTR, AnimationInfo attackFTL,
		AnimationInfo hitFR, AnimationInfo hitFL, AnimationInfo hitFTR, AnimationInfo hitFTL, AnimationInfo deathFR)
		: idleR{ idleFR }, idleL{ idleFL }, idleTR{ idleFTR }, idleTL{ idleFTL },
		moveR{ moveFR }, moveL{ moveFL }, moveTR{ moveFTR }, moveTL{ moveFTL },
		attackR{ attackFR }, attackL{ attackFL }, attackTR{ attackFTR }, attackTL{ attackFTL },
		hitR{ hitFR }, hitL{ hitFL }, hitTR{ hitFTR }, hitTL{ hitFTL }, death{ deathFR }
	{

	}

};

struct TileInfo 
{
public:

	std::string name{ "grass" };
	float sortOrder{ -10 };
	AnimationInfo animInfo{ "grass", {0,1,0.0f,0,false} , {-5,0,0.0f,0,false}, { 0,0 } };
	bool dynamicSort{ false };

	TileInfo()
		: TileInfo("grass", -10, { "grass", {0,1,0.0f,0,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false)
	{
	}

	TileInfo(std::string n, float s, AnimationInfo a, bool d)
		: name{ n }, sortOrder{ s }, animInfo{ a }, dynamicSort{ d }
	{}

};

struct CollisionInfo
{
public:

	CollisionInfo()
		: CollisionInfo(false, false, { 0,0,0,0 }, { 0,0,0,0 })
	{}

	CollisionInfo(bool c, bool t, Transform c1, Transform c2)
		: collided{ c }, trigger{ t }, c1_transform{ c1 }, c2_transform{ c2 }
	{}

	bool collided{ false };
	bool trigger{ false };

	Transform c1_transform{ 0,0,0,0 };
	Transform c2_transform{ 0,0,0,0 };

};

struct Collided 
{
public:

	Collided()
		: Collided(nullptr, { false, false, { 0,0,0,0 }, { 0,0,0,0 }})
	{}

	Collided(GameObject* g, CollisionInfo i)
		: gameObject{ g }, info{ i }
	{}

	GameObject* gameObject;

	CollisionInfo info;

};