#include "pch.h"
#include "HUD.h"

#include "UI/HealthBar/HealthBar.h"
#include "UI/ManaBallCounter/ManaBallCounter.h"

Client::UI::HUD::HUD(const Engine::Math::Vector2& size)
    : Anchor(size), _isShown(true)
{
    SetPadding({40, 32, 40, 32});
    CreateChild<HealthBar>();
    auto [anchorChild, counter] = CreateChild<UI::ManaBallCounter>();
    counter->SetMargin({128, 72, 0, 0});
}

void Client::UI::HUD::Render(const Engine::Manager::Render::Renderer renderer, const Engine::Math::Rect baseRect)
{
    if (_isShown) Anchor::Render(renderer, baseRect);
}

void Client::UI::HUD::Hide()
{
    _isShown = false;
}

void Client::UI::HUD::Show()
{
    _isShown = true;
}

bool Client::UI::HUD::IsShown() const
{
    return _isShown;
}
