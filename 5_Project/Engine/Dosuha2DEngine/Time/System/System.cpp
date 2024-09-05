#include "pch.h"
#include "System.h"

Time::System::System()
    : _deltaTime(0), _timeScale(1)
{
}

void Time::System::Initialize() noexcept
{
    _currentTime = std::chrono::steady_clock::now();
}

void Time::System::Update() noexcept
{
    _previousTime = _currentTime;
    _currentTime = std::chrono::steady_clock::now();
    _deltaTime = std::chrono::duration<float>(_currentTime - _previousTime).count();
}

float Time::System::SetTimeScale(const float timeScale) noexcept
{
    const float previousTimeScale = _timeScale;
    _timeScale = timeScale;
    return previousTimeScale;
}

float Time::System::GetTimeScale() const noexcept
{
    return _timeScale;
}

float Time::System::GetDeltaMetaTime() const noexcept
{
    return _deltaTime;
}

float Time::System::GetDeltaGameTime() const noexcept
{
    return _deltaTime * _timeScale;
}
