#pragma once

#include <SDL.h>

static class Time
{
public:

	static void Update();

	static float GetDeltaTime();

private:

	static float m_currentFrameTime;
	static float m_previousFrameTime;
};

