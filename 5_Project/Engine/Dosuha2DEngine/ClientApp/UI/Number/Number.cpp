#include "pch.h"
#include "Number.h"

Client::UI::Number::Number(const Engine::Math::Vector2& size)
    : Image(size, L"Resources/Sprites/UI/UI_002.png"), _sourceRect(Engine::Math::Rect(0, 0, 300, 300)), _number(0)
{
}

void Client::UI::Number::Render(const Engine::Manager::Render::Renderer renderer, const Engine::Math::Rect baseRect)
{
    const Engine::Math::Rect childRect = GetChildRect(baseRect);
    _sourceRect.left = GetSourceLeft();
    _sourceRect.right = _sourceRect.left + 300;
    renderer->DrawBitmap(_bitmap, childRect, _sourceRect);
    if (_child != nullptr) _child->Render(renderer, childRect);
}

void Client::UI::Number::SetNumber(const int number)
{
    _number = number;
}

int Client::UI::Number::GetNumber() const
{
    return _number;
}

float Client::UI::Number::GetSourceLeft() const
{
    switch (_number)
    {
    case -2: return 3300;
    case -1: return 3000;
    case 1: return 0;
    case 2: return 300;
    case 3: return 600;
    case 4: return 900;
    case 5: return 1200;
    case 6: return 1500;
    case 7: return 1800;
    case 8: return 2100;
    case 9: return 2400;
    case 0: default: return 2700;
    }
}
