#pragma once

namespace Client::UI
{
    class Card;

    class Upgrade : public Engine::UI::Panel::Anchor
    {
    public:
        using Event = std::function<void()>;
        
        explicit Upgrade(const Engine::Math::Vector2& size);

        void Initialize(Engine::Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect) override;
        void Finalize() override;

        void Hide();
        void Show();

        [[nodiscard]] bool IsShown() const;

        void BindOnUpgradeComplete(const Event& event);

        void Reset();

    protected:
        void UpdateCardOpen(float deltaTime);
        void UpdateUpgradeComplete(float deltaTime);

    private:
        std::shared_ptr<Engine::UI::Wrapper::Animation> _book;
        std::shared_ptr<Card> _healthCard;
        std::shared_ptr<Card> _manaBallCard;
        std::shared_ptr<Card> _speedCard;
        std::shared_ptr<Engine::UI::Wrapper::FadeImage> _text;
        bool _isShown;
        float _cardOpenElapsedTime;
        float _cardOpenDelay;
        bool _isCardOpen;
        bool _isUpgrade;

        Event _onUpgradeComplete;
        float _upgradeCompleteDelay;
        float _upgradeCompleteElapsedTime;
        std::unique_ptr<::Audio::ISound> _cardOpenSound;
        std::unique_ptr<::Audio::ISound> _upgradeCompleteSound;
    };
}
