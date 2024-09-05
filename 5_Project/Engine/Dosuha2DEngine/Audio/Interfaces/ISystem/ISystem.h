#pragma once

namespace Audio
{
    struct ISystem
    {
        ISystem() = default;
        ISystem(const ISystem& other) = delete;
        ISystem(ISystem&& other) noexcept = delete;
        ISystem& operator=(const ISystem& other) = delete;
        ISystem& operator=(ISystem&& other) noexcept = delete;
        virtual ~ISystem() = default;

        virtual void Update() = 0;

        virtual ISound* SetAudio(const char* path, Audio::ChannelGroupType group, bool isLoop) = 0;

        virtual void Pause() = 0;
        virtual void Pause(Audio::ChannelGroupType group) = 0;
        virtual void Resume() = 0;
        virtual void Resume(Audio::ChannelGroupType group) = 0;
        virtual void Stop() = 0;
        virtual void Stop(Audio::ChannelGroupType group) = 0;
        virtual void SetVolume(float volume) = 0;
        virtual void SetVolume(Audio::ChannelGroupType group, float volume) = 0;
        virtual void Mute() = 0;
        virtual void Mute(Audio::ChannelGroupType group) = 0;
        virtual void Unmute() = 0;
        virtual void Unmute(Audio::ChannelGroupType group) = 0;
    };
}
