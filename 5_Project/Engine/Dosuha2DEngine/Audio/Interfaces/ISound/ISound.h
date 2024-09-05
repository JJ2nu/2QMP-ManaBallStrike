#pragma once

namespace Audio
{
    struct ISound
    {
        ISound() = default;
        ISound(const ISound& other) = default;
        ISound(ISound&& other) noexcept = default;
        ISound& operator=(const ISound& other) = default;
        ISound& operator=(ISound&& other) noexcept = default;
        virtual ~ISound() = default;

        virtual void Play() = 0;
        virtual void Stop() = 0;
        [[nodiscard]] virtual bool IsPlaying() const = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;
        [[nodiscard]] virtual bool IsPaused() const = 0;

        virtual void SetVolume(float volume) = 0;
        [[nodiscard]] virtual float GetVolume() const = 0;

        virtual void Mute() = 0;
        virtual void Unmute() = 0;
        [[nodiscard]] virtual bool IsMuted() const = 0;

        virtual void FadeIn(float fadeTime = 2.f) = 0;
        virtual void FadeOut(float fadeTime = 2.f) = 0;

        virtual void SetDelay(float delayTime = 1.f) = 0;

        [[nodiscard]] virtual float GetLength() const = 0;
    };
}
