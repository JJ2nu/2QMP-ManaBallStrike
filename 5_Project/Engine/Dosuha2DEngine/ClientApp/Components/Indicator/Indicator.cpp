#include "pch.h"
#include "Indicator.h"

Client::Component::Indicator::Indicator()
    : Bitmap(L"Resources/Sprites/UI/UI_009.png")
{
}

void Client::Component::Indicator::Update(float deltaMetaTime, float deltaGameTime)
{
    SetRotation(_direction.AngleByAxisX() * Engine::Math::Helper::RadianToDegree + 90.f);
    Bitmap::Update(deltaMetaTime, deltaGameTime);
}

void Client::Component::Indicator::SetDirection(const Engine::Math::Vector2& direction)
{
    _direction = direction.Normalize();
}

Engine::Math::Vector2 Client::Component::Indicator::GetDirection() const
{
    return _direction;
}
