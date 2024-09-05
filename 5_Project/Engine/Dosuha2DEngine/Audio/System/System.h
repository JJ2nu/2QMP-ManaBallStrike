#pragma once

namespace Audio
{
    class Sound;

    class System : public ISystem
    {
    public:
        System();
        System(const System& other) = delete;
        System(System&& other) noexcept = delete;
        System& operator=(const System& other) = delete;
        System& operator=(System&& other) noexcept = delete;
        ~System() override;

        void Update() override;

        ISound* SetAudio(const char* path, Audio::ChannelGroupType group, bool isLoop) override;

        void Pause() override;
        void Pause(Audio::ChannelGroupType group) override;
        void Resume() override;
        void Resume(Audio::ChannelGroupType group) override;
        void Stop() override;
        void Stop(Audio::ChannelGroupType group) override;
        void SetVolume(float volume) override;
        void SetVolume(Audio::ChannelGroupType group, float volume) override;
        void Mute() override;
        void Mute(Audio::ChannelGroupType group) override;
        void Unmute() override;
        void Unmute(Audio::ChannelGroupType group) override;
        
    private:
        FMOD::System* _system;
        FMOD::ChannelGroup* _masterGroup;
        std::map<ChannelGroupType, FMOD::ChannelGroup*> _channelGroups;
    };
}
