#include "pch.h"
#include "GameOver.h"

Client::UI::GameOver::GameOver(const Engine::Math::Vector2& size)
    : Anchor(size), _isShown(false), _onRestart(nullptr), _elapsedTime(0.f), _restartDelay(Manager::Config::GetSection(L"System")->GetFloat(L"GameOverRestartDelay")),
      _requestRestart(false)
{
    auto [boxAnchorChild, background] = CreateChild<Engine::UI::Wrapper::Box>(
        Engine::Math::Vector2{size}, D2D1::ColorF(D2D1::ColorF::Black, 0.7f));
    auto [_1, animation] = CreateChild<Engine::UI::Wrapper::Animation>(Engine::Math::Vector2{1500, 400},
                                                                       L"Resources/Sprites/UI/icon_006.png",
                                                                       L"Resources/Animation/GameOver/GameOver.csv");
    _1->SetAnchoring(AnchorChild::HorizontalAnchoring::Center, AnchorChild::VerticalAnchoring::Center);
    _animation = animation;
}

void Client::UI::GameOver::Initialize(Engine::Manager::Resource::Loader loader)
{
    Anchor::Initialize(loader);
    _animation->SetMotion(L"Over");
}

void Client::UI::GameOver::Update(float deltaMetaTime, float deltaGameTime)
{
    if (_isShown)
    {
        Anchor::Update(deltaMetaTime, deltaGameTime);
        UpdateRestart(deltaMetaTime);
    }
}

void Client::UI::GameOver::LazyUpdate(float deltaMetaTime, float deltaGameTime)
{
    if (_isShown) Anchor::LazyUpdate(deltaMetaTime, deltaGameTime);
}

void Client::UI::GameOver::Render(Engine::Manager::Render::Renderer renderer, Engine::Math::Rect baseRect)
{
    if (_isShown) Anchor::Render(renderer, baseRect);
}

void Client::UI::GameOver::UpdateRestart(float deltaTime)
{
    if (_requestRestart) return;
    _elapsedTime += deltaTime;
    if (_elapsedTime < _restartDelay) return;
    if (_onRestart) _onRestart();
    _requestRestart = true;
}

void Client::UI::GameOver::BindOnRestart(Event event)
{
    _onRestart = std::move(event);
}

void Client::UI::GameOver::Reset()
{
    _elapsedTime = 0.f;
    _requestRestart = false;
}

void Client::UI::GameOver::Show()
{
    _isShown = true;
}

void Client::UI::GameOver::Hide()
{
    _isShown = false;
}
