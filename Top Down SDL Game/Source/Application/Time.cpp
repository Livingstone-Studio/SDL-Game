#include "Time.h"

float Time::m_currentFrameTime = 0;
float Time::m_previousFrameTime = 0;

void Time::Update()
{
    m_previousFrameTime = m_currentFrameTime;
    m_currentFrameTime = SDL_GetTicks();
}

float Time::GetDeltaTime() // May need rework.
{
    float dt = (m_currentFrameTime - m_previousFrameTime) * 60.00f / 100000;

    if (dt > 1.5f)
    {
        dt = 1.5f;
    }

    return dt;
}