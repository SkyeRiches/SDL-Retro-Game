#include "..\include\Timer.h"

Timer* Timer::m_sInstance = NULL;

/// <summary>
/// Creates an instance of the timer
/// </summary>
/// <returns></returns>
Timer* Timer::Instance()
{
    if (m_sInstance == NULL)
    {
        m_sInstance = new Timer();
    }
    return m_sInstance;
}

/// <summary>
/// Deletes the current instance of the timer
/// </summary>
void Timer::Release()
{
    delete m_sInstance;
    m_sInstance = NULL;
}

/// <summary>
/// Returns the change in time since the last frame
/// </summary>
/// <returns></returns>
float Timer::DeltaTime()
{
    return m_fDeltaTime;
}

/// <summary>
/// Changes the rate at which time passes
/// </summary>
/// <param name="a_fScale"></param>
void Timer::SetTimeScale(float a_fScale)
{
    m_fTimeScale = a_fScale;
}

/// <summary>
/// Returns the current rate of time passage
/// </summary>
/// <returns></returns>
float Timer::GetTimeScale()
{
	return m_fTimeScale;
}

/// <summary>
/// increases the time each occurence of the function
/// </summary>
void Timer::Update()
{
    m_uiElapsedTicks = SDL_GetTicks() - m_uiStartTicks;
    m_fDeltaTime = m_uiElapsedTicks * 0.001f; // Convert From ms to s
}

/// <summary>
/// Sets the timer back to 0
/// </summary>
void Timer::Reset()
{
    m_uiStartTicks = SDL_GetTicks();
    m_uiElapsedTicks = 0;
    m_fDeltaTime = 0.0f;
}

/// <summary>
/// Constructor for timer
/// </summary>
Timer::Timer()
{
    Reset();
    m_fTimeScale = 1.0f;
}

Timer::~Timer()
{
}
