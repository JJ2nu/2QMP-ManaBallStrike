#include "pch.h"
#include "TimeManager.h"

void Engine::Manager::Time::Initialize() noexcept
{
    GetInstance()->_system = std::unique_ptr<::Time::ISystem>(::Time::CreateSystem());
    GetInstance()->_system->Initialize();
}

void Engine::Manager::Time::Update() noexcept
{
    GetInstance()->_system->Update();
}

float Engine::Manager::Time::SetTimeScale(const float timeScale) noexcept
{
    return GetInstance()->_system->SetTimeScale(timeScale);
}

float Engine::Manager::Time::GetTimeScale() noexcept
{
    return GetInstance()->_system->GetTimeScale();
}

float Engine::Manager::Time::GetDeltaMetaTime() noexcept
{
    return GetInstance()->_system->GetDeltaMetaTime();
}

float Engine::Manager::Time::GetDeltaGameTime() noexcept
{
    return GetInstance()->_system->GetDeltaGameTime();
}

Engine::Manager::Time::Time()
    : _system(nullptr)
{
}