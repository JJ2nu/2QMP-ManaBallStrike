#include "pch.h"
#include "System.h"
#include "../Sound/Sound.h"


Audio::System::System()
{
    System_Create(&_system);
    int channelNumber;
    _system->getSoftwareChannels(&channelNumber);
    _system->init(channelNumber, FMOD_INIT_NORMAL, nullptr);
    _system->createChannelGroup("Background", &_channelGroups[ChannelGroupType::Background]);
    _system->createChannelGroup("Effect", &_channelGroups[ChannelGroupType::Effect]);
    _system->getMasterChannelGroup(&_masterGroup);
    for (const auto& group : _channelGroups | std::views::values)
    {
        _masterGroup->addGroup(group);
    }
}

Audio::System::~System()
{
    _masterGroup->release();
    for (const auto& group : _channelGroups | std::views::values)
    {
        group->release();
    }
    _system->close();
    _system->release();
}

void Audio::System::Update()
{
    _system->update();
}

Audio::ISound* Audio::System::SetAudio(const char* path, const ChannelGroupType group, const bool isLoop)
{
    Sound* sound = new Sound(_system, _channelGroups[group], path, isLoop);
    return sound;
}

void Audio::System::Pause()
{
    bool isPlaying;
    _masterGroup->isPlaying(&isPlaying);
    if (!isPlaying) return;
    _masterGroup->setPaused(true);
}

void Audio::System::Pause(const ChannelGroupType group)
{
    bool isPlaying;
    _channelGroups[group]->isPlaying(&isPlaying);
    if (!isPlaying) return;
    _channelGroups[group]->setPaused(true);
}

void Audio::System::Resume()
{
    bool isPlaying;
    _masterGroup->isPlaying(&isPlaying);
    if (isPlaying) return;
    _masterGroup->setPaused(false);
}

void Audio::System::Resume(const ChannelGroupType group)
{
    bool isPlaying;
    _channelGroups[group]->isPlaying(&isPlaying);
    if (isPlaying) return;
    _channelGroups[group]->setPaused(false);
}

void Audio::System::Stop()
{
    _masterGroup->stop();
}

void Audio::System::Stop(const ChannelGroupType group)
{
    _channelGroups[group]->stop();
}

void Audio::System::SetVolume(const float volume)
{
    _masterGroup->setVolume(volume);
}

void Audio::System::SetVolume(const ChannelGroupType group, const float volume)
{
    _channelGroups[group]->setVolume(volume);
}

void Audio::System::Mute()
{
    bool isMute;
    _masterGroup->getMute(&isMute);
    if (isMute) return;
    _masterGroup->setMute(true);
}

void Audio::System::Mute(const ChannelGroupType group)
{
    bool isMute;
    _channelGroups[group]->getMute(&isMute);
    if (isMute) return;
    _channelGroups[group]->setMute(true);
}

void Audio::System::Unmute()
{
    bool isMute;
    _masterGroup->getMute(&isMute);
    if (!isMute) return;
    _masterGroup->setMute(false);
}

void Audio::System::Unmute(const ChannelGroupType group)
{
    bool isMute;
    _channelGroups[group]->getMute(&isMute);
    if (!isMute) return;
    _channelGroups[group]->setMute(false);
}
