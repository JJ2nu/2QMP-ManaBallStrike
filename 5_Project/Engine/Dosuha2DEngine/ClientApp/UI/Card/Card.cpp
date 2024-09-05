#include "pch.h"
#include "Card.h"

Client::UI::Card::Card(const Engine::Math::Vector2& size, std::filesystem::path cardImagePath,
                       std::filesystem::path cardTextImagePath)
    : Stack(size), _cardImagePath(std::move(cardImagePath)), _cardTextImagePath(std::move(cardTextImagePath)),
      _isActivate(false),
      _elapsedTime(0), _cardUpDuration(0.5f), _isCardUp(false), _initialCardY(40), _currentCardY(0)
{
    SetOrientation(Orientation::Vertical);

    auto [overlayStackChild, overlay]
        = CreateChild<Engine::UI::Panel::Overlay>(Engine::Math::Vector2{size.x, size.x * 1.5f});

    auto [cardOverlayChild, card]
        = overlay->CreateChild<Engine::UI::Wrapper::FadeImage>(Engine::Math::Vector2{size.x, size.x * 1.5f},
                                                               _cardImagePath);
    _cardImage = card;
    auto [buttonOverlayChild, button]
        = overlay->CreateChild<Engine::UI::Wrapper::Button>(Engine::Math::Vector2{size.x, size.x * 1.5f});
    _button = button;

    auto [blankStackChild, blank] = CreateChild<Engine::UI::Wrapper::Box>(
        Engine::Math::Vector2{size.x, size.x * 0.1f}, D2D1::ColorF(D2D1::ColorF::White, 0.0f));
    auto [textStackChild, text] = CreateChild<Engine::UI::Wrapper::FadeImage>(
        Engine::Math::Vector2{size.x, size.x * 0.4f}, _cardTextImagePath);
    button->BindOnHoverBegin([text] { text->FadeIn(); });
    button->BindOnHoverEnd([text] { text->FadeOut(); });
    _cardImage->BindOnFadeOutEnd([this] { _isActivate = false; });
}

void Client::UI::Card::Update(float deltaMetaTime, float deltaGameTime)
{
    if (_isActivate)
    {
        Stack::Update(deltaMetaTime, deltaGameTime);
        UpdateCardUp(deltaGameTime);
    }
}

void Client::UI::Card::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
    if (_isActivate) Stack::LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Client::UI::Card::Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect)
{
    if (_isActivate)
    {
        baseRect.MoveY(_currentCardY);
        Stack::Render(renderer, baseRect);
    }
}

void Client::UI::Card::BindOnClick(const Event& event) const
{
    _button->BindOnClick(event);
}

void Client::UI::Card::Activate()
{
    _isActivate = true;
    _cardImage->FadeIn();
}

void Client::UI::Card::Deactivate()
{
    _cardImage->FadeOut();
}

void Client::UI::Card::Reset()
{
    _cardImage->Reset();
    _isActivate = false;
    _elapsedTime = 0.0f;
    _isCardUp = false;
    _currentCardY = _initialCardY;
}

void Client::UI::Card::UpdateCardUp(float deltaTime)
{
    if (_isCardUp) return;
    _elapsedTime += deltaTime;
    float time = Engine::Math::Helper::Min()(_elapsedTime / _cardUpDuration, 1.f);
    _currentCardY = Engine::Math::Helper::Lerp()(_initialCardY, 0, time);
    if (time == 1.f) _isCardUp = true;
}
