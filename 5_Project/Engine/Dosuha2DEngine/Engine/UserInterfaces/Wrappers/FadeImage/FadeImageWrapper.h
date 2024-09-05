#include <utility>

#pragma once

namespace Engine::UI::Wrapper
{
    class FadeImage : public Image
    {
        enum class State
        {
            None,
            FadeIn,
            FadeOut,
        };

    public:
        using Event = std::function<void()>;
        FadeImage(const Math::Vector2& size, std::wstring path);

        void FadeIn();
        void FadeOut();

        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;

        void SetDuration(float duration);
        void SetOpacity(float opacity);

        void BindOnFadeInEnd(Event event);
        void BindOnFadeOutEnd(Event event);

        void Reset();

    protected:
        void UpdateFade(float deltaTime);

    private:
        float _opacity;
        float _duration;
        float _elapsedTime;
        State _state;
        Event _onFadeInEnd;
        Event _onFadeOutEnd;
    };
}
