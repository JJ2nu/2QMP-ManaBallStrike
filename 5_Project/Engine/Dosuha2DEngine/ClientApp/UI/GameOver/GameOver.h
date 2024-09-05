#pragma once

namespace Client::UI
{
    class GameOver : public Engine::UI::Panel::Anchor
    {
    public:
        using Event = std::function<void()>;
        GameOver(const Engine::Math::Vector2& size);

        void Initialize(Engine::Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect) override;
        
        void UpdateRestart(float deltaTime);

        void BindOnRestart(Event event);

        void Reset();

        void Show();
        void Hide();

    private:
        bool _isShown;
        std::shared_ptr<Engine::UI::Wrapper::Animation> _animation;
        Event _onRestart;
        float _elapsedTime;
        float _restartDelay;
        bool _requestRestart;
    };
}
