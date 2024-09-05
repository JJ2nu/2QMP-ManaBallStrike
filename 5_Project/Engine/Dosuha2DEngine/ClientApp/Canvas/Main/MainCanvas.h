#pragma once

namespace Client::UI
{
    class HUD;
    class Settings;
    class Upgrade;
    class GameOver;
}

namespace Client::Canvas
{
    class Main : public Engine::Canvas
    {
    public:
        using Event = std::function<void()>;
        
        explicit Main(const Engine::Math::Vector2& viewportSize);

        void ShowUpgrade() const;
        void HideUpgrade() const;

        void ShowSettings() const;
        void HideSettings() const;
        
        void ShowHUD() const;
        void HideHUD() const;

        void BindOnUpgradeComplete(Event event);

        void ResetUpgrade() const;

        void BindOnQuit(const Event& event) const;
        void BindOnRestart(const Event& event) const;

        void FadeIn() const;
        void FadeOut() const;
        
        void ShowGameOver() const;
        void HideGameOver() const;

        void BindOnFadeInEnd(Event event) const;
        void BindOnFadeOutEnd(Event event) const;

    protected:
        void OnCreateUserInterface() override;
        void OnSetup() override;


    private:
        Engine::Math::Vector2 _viewportSize;
        std::shared_ptr<UI::HUD> _hud;
        std::shared_ptr<UI::Settings> _settings;
        std::shared_ptr<UI::Upgrade> _upgrade;
        std::shared_ptr<Engine::UI::Wrapper::FadeImage> _FadeImage;
        std::shared_ptr<UI::GameOver> _gameOver;
        Event _onUpgradeComplete;
    };
}
