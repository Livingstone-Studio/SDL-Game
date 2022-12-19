#pragma once

#include <string>

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

	AnimClipInfo()
		: AnimClipInfo(0, 0, 1.0f, 0, true)
	{
	}

	AnimClipInfo(int r, int sC, float t, int s, bool l)
		: row{ r }, spriteCount{ sC }, animTimeBetween{ t }, start{ s }, looping{ l }
	{
	}

};

struct AnimationInfo 
{
public:

	std::string name{ "" };

	AnimClipInfo actionAnimClip;
	AnimClipInfo actionAnimShadow;

	AnimationInfo() 
	{
	}

	AnimationInfo(std::string n, AnimClipInfo action, AnimClipInfo shadow)
		: name{ n }, actionAnimClip { action }, actionAnimShadow{ shadow }
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

	CharacterAnimInfo() 
	{

	}

	CharacterAnimInfo(std::string path, AnimationInfo idleFR, AnimationInfo idleFL, AnimationInfo idleFTR, AnimationInfo idleFTL,
		AnimationInfo moveFR, AnimationInfo moveFL, AnimationInfo moveFTR, AnimationInfo moveFTL,
		AnimationInfo attackFR, AnimationInfo attackFL, AnimationInfo attackFTR, AnimationInfo attackFTL)
		: idleR{ idleFR }, idleL{ idleFL }, idleTR{ idleFTR }, idleTL{ idleFTL },
		moveR{ moveFR }, moveL{ moveFL }, moveTR{ moveFTR }, moveTL{ moveFTL },
		attackR{ attackFR }, attackL{ attackFL }, attackTR{ attackFTR }, attackTL{ attackFTL }
	{

	}

};