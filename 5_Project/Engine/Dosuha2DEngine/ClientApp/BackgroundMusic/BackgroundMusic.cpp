#include "pch.h"
#include "BackgroundMusic.h"

Client::BackgroundMusic::BackgroundMusic(std::filesystem::path path)
	: _path(std::move(path))
{
}

void Client::BackgroundMusic::Load()
{
	_backgroundMusic = Engine::Manager::Audio::CreateSound(_path, Audio::ChannelGroupType::Background, true);
}

void Client::BackgroundMusic::Load(const bool isLoop)
{
	_backgroundMusic = Engine::Manager::Audio::CreateSound(_path, Audio::ChannelGroupType::Background, isLoop);
}

void Client::BackgroundMusic::Load(std::filesystem::path path)
{
	_backgroundMusic = Engine::Manager::Audio::CreateSound(path, Audio::ChannelGroupType::Background, true);
}

void Client::BackgroundMusic::Release()
{
	_backgroundMusic = nullptr;
}

void Client::BackgroundMusic::Play() const
{
	_backgroundMusic->Play();
}

bool Client::BackgroundMusic::IsPlaying() const
{
	return _backgroundMusic->IsPlaying();
}
