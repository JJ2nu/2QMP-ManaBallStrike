#pragma once

namespace Engine::Component
{
    class FadeBitmap : public AlphaBitmap
    {
        enum class State : uint8_t
        {
            None,
            FadeIn,
            FadeOut
        };

    public:
        using Event = std::function<void()>;

        FadeBitmap(std::wstring path);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void FadeIn();
        void FadeOut();

        void SetDuration(float duration);
        
        void BindOnFadeInEnd(Event event);
        void BindOnFadeOutEnd(Event event);

    private:
        void UpdateFade(float deltaTime);

        float _duration;
        float _elapsedTime;
        State _state;
        Event _onFadeInEnd;
        Event _onFadeOutEnd;
    };
}
