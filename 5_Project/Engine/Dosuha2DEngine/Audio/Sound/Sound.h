#pragma once

namespace Audio
{
    class Sound : public ISound
    {
    public:
        Sound(FMOD::System* system, FMOD::ChannelGroup* group, const char* path, bool isLoop);
        Sound(const Sound& other) = delete;
        Sound(Sound&& other) noexcept = delete;
        Sound& operator=(const Sound& other) = delete;
        Sound& operator=(Sound&& other) noexcept = delete;
        ~Sound() override;

        void Play() override;
        void Stop() override;
        [[nodiscard]] bool IsPlaying() const override;
        void Pause() override;
        void Resume() override;
        [[nodiscard]] bool IsPaused() const override;
        void SetVolume(float volume) override;
        [[nodiscard]] float GetVolume() const override;
        void Mute() override;
        void Unmute() override;
        [[nodiscard]] bool IsMuted() const override;
        void FadeIn(float fadeTime) override;
        void FadeOut(float fadeTime) override;
        void SetDelay(float delayTime) override;
        [[nodiscard]] float GetLength() const override;

    private:
        [[nodiscard]] unsigned long long GetDspClock() const;
        [[nodiscard]] unsigned long long GetSampleRateTime(float time) const;
        [[nodiscard]] unsigned int GetPosition() const;

        FMOD::System* _system;
        FMOD::Channel* _channel;
        FMOD::Sound* _sound;
        FMOD::ChannelGroup* _group;
        int _rate;
    };
}
