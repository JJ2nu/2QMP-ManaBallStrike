#pragma once

namespace Client::UI
{
    class Card : public Engine::UI::Panel::Stack
    {
    public:
        using Event = std::function<void()>;
        Card(const Engine::Math::Vector2& size, std::filesystem::path cardImagePath,
             std::filesystem::path cardTextImagePath);

        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect) override;

        void BindOnClick(const Event& event) const;

        void Activate();
        void Deactivate();

        void Reset();

    protected:
        void UpdateCardUp(float deltaTime);

    private:
        std::filesystem::path _cardImagePath;
        std::filesystem::path _cardTextImagePath;

        std::shared_ptr<Engine::UI::Wrapper::Button> _button;
        std::shared_ptr<Engine::UI::Wrapper::FadeImage> _cardImage;
        bool _isActivate;

        float _elapsedTime;
        float _cardUpDuration;
        bool _isCardUp;
        float _initialCardY;
        float _currentCardY;
    };
}
