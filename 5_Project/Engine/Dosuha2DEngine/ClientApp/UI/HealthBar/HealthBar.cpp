#include "pch.h"
#include "HealthBar.h"

Client::UI::HealthBar::HealthBar()
    : Overlay(Engine::Math::Vector2{600, 100}), _barWidth(452)
{
    auto [overlayBoxChild, box]
        = CreateChild<Engine::UI::Wrapper::Box>
        (Engine::Math::Vector2{_barWidth, 28}, D2D1::ColorF(D2D1::ColorF::Red));
    _bar = box;
    _bar->SetMargin(Engine::Math::Rect{92, 24, 56, 48});
    auto [overlayImageChild, image]
        = CreateChild<Engine::UI::Wrapper::Image>
        (Engine::Math::Vector2{600, 100}, L"Resources/Sprites/UI/UI_003.png");
    auto [overlayAnimationChild, animation]
        = CreateChild<Engine::UI::Wrapper::Animation>
        (Engine::Math::Vector2{64, 64}, L"Resources/Sprites/UI/UI_010.png", L"Resources/Animation/UI/Heart/Heart.csv");
    animation->SetMargin(Engine::Math::Rect{18, 18, 0, 0});
}

void Client::UI::HealthBar::Initialize(const Engine::Manager::Resource::Loader loader)
{
    Overlay::Initialize(loader);
    Engine::Manager::Observer<float>::Register(L"HealthPoint", [this](const float value)
    {
        const float currentRatio = static_cast<float>(value) / Manager::Data::GetMaxHealthPoint();
        _bar->SetSize({currentRatio * _barWidth, 28});
    });
}
