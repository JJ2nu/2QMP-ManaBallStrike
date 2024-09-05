#pragma once

namespace Client::UI
{
    class Settings : public Engine::UI::Panel::Anchor
    {
    public:
        using Event = std::function<void()>;
        
        explicit Settings(const Engine::Math::Vector2& size);

        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect) override;

        void Hide();
        void Show();

        [[nodiscard]] bool IsShown() const;

        void BindOnQuit(const Event& event) const;
        void BindOnRestart(const Event& event) const;

    private:
        bool _isShown;
        Engine::Math::Vector2 _backgroundSize;
        float _maxValue;
        float _defaultRightPadding;
        std::shared_ptr<Engine::UI::Wrapper::Image> _masterBar;
        std::shared_ptr<Engine::UI::Wrapper::Image> _backgroundBar;
        std::shared_ptr<Engine::UI::Wrapper::Button> _restartButton;
        std::shared_ptr<Engine::UI::Wrapper::Button> _quitButton;
    };
}
