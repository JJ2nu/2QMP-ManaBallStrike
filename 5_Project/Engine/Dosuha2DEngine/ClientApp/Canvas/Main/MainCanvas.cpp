#include "pch.h"
#include "MainCanvas.h"

#include "UI/HUD/HUD.h"
#include "UI/Settings/Settings.h"
#include "UI/Upgrade/Upgrade.h"
#include "UI/GameOver/GameOver.h"

Client::Canvas::Main::Main(const Engine::Math::Vector2& viewportSize)
    : Canvas(viewportSize), _viewportSize(viewportSize)
{
}

void Client::Canvas::Main::OnCreateUserInterface()
{
    auto [_1, overlay] = _rootPanel->CreateChild<Engine::UI::Panel::Overlay>(_viewportSize);
    auto [_4, hud] = overlay->CreateChild<UI::HUD>(_viewportSize);
    _hud = hud;
    auto [_3, upgrade] = overlay->CreateChild<UI::Upgrade>(_viewportSize);
    _upgrade = upgrade;
    auto [_6, gameOver] = overlay->CreateChild<UI::GameOver>(_viewportSize);
    _gameOver = gameOver;
    auto [_2, settings] = overlay->CreateChild<UI::Settings>(_viewportSize);
    _settings = settings;
    auto [_5, fadeImage] = overlay->CreateChild<Engine::UI::Wrapper::FadeImage>(
        _viewportSize, L"Resources/Sprites/UI/FadeMask.png");
    _FadeImage = fadeImage;
}

void Client::Canvas::Main::OnSetup()
{
    _settings->Hide();
    const auto playerContext = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Settings");
    playerContext->AddListener(Input::TriggerState::Started, [this](const Input::Value& _)
    {
        if (_settings->IsShown()) HideSettings();
        else ShowSettings();
    });
    _upgrade->BindOnUpgradeComplete([this]
    {
        HideUpgrade();
        ShowHUD();
        if (_onUpgradeComplete != nullptr) _onUpgradeComplete();
    });

    _FadeImage->Reset();
    _FadeImage->SetDuration(1.f);
}

void Client::Canvas::Main::ShowSettings() const
{
    _settings->Show();
    Engine::Manager::Time::SetTimeScale(0.0f);
}

void Client::Canvas::Main::HideSettings() const
{
    _settings->Hide();
    Engine::Manager::Time::SetTimeScale(1.0f);
}

void Client::Canvas::Main::ShowHUD() const
{
    _hud->Show();
}

void Client::Canvas::Main::HideHUD() const
{
    _hud->Hide();
}

void Client::Canvas::Main::BindOnUpgradeComplete(Event event)
{
    _onUpgradeComplete = std::move(event);
}

void Client::Canvas::Main::ResetUpgrade() const
{
    _upgrade->Reset();
}

void Client::Canvas::Main::BindOnQuit(const Event& event) const
{
    _settings->BindOnQuit(event);
}

void Client::Canvas::Main::BindOnRestart(const Event& event) const
{
    auto function = [this, event]
    {
        event();
        _gameOver->Reset();
    };
    _settings->BindOnRestart(function);
    _gameOver->BindOnRestart(function);
}

void Client::Canvas::Main::FadeIn() const
{
    _FadeImage->FadeIn();
}

void Client::Canvas::Main::FadeOut() const
{
    _FadeImage->FadeOut();
}

void Client::Canvas::Main::ShowGameOver() const
{
    _gameOver->Show();
}

void Client::Canvas::Main::HideGameOver() const
{
    _gameOver->Hide();
}

void Client::Canvas::Main::BindOnFadeInEnd(Event event) const
{
    _FadeImage->BindOnFadeInEnd(std::move(event));
}

void Client::Canvas::Main::BindOnFadeOutEnd(Event event) const
{
    _FadeImage->BindOnFadeOutEnd(std::move(event));
}

void Client::Canvas::Main::ShowUpgrade() const
{
    _upgrade->Show();
}

void Client::Canvas::Main::HideUpgrade() const
{
    _upgrade->Hide();
}
