#include "pch.h"
#include "AudioManager.h"

#include <filesystem>

void Engine::Manager::Audio::Initialize()
{
    ::Audio::ISystem* system;
    CreateSystem(&system);
    GetInstance()->_system = std::unique_ptr<::Audio::ISystem>(system);
}

std::unique_ptr<Audio::ISound> Engine::Manager::Audio::CreateSound(const std::filesystem::path& path,
                                                                   const ::Audio::ChannelGroupType type,
                                                                   const bool isLoop)
{
    return std::unique_ptr<::Audio::ISound>(GetInstance()->_system->SetAudio(path.string().c_str(), type, isLoop));
}

void Engine::Manager::Audio::Update()
{
    GetInstance()->_system->Update();
}

void Engine::Manager::Audio::Finalize()
{
    GetInstance()->_system = nullptr;
}

void Engine::Manager::Audio::SetVolume(const float volume)
{
    GetInstance()->_system->SetVolume(volume);
}

void Engine::Manager::Audio::SetVolume(const ::Audio::ChannelGroupType group, const float volume)
{
    GetInstance()->_system->SetVolume(group, volume);
}
