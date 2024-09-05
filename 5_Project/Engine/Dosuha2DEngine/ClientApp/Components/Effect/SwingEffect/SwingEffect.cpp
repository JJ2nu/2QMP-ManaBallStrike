#include "pch.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"
#include "SwingEffect.h"
Client::Component::SwingEffect::SwingEffect(std::wstring path, std::wstring motion)
    :EventBindAnimation(path, motion)
{
}

void Client::Component::SwingEffect::Update(float deltaMetaTime, float deltaGameTime)
{
    float degree = GetDegree();
    SetRotation(degree);
    EventBindAnimation::Update(deltaMetaTime, deltaGameTime);
}

float Client::Component::SwingEffect::GetDegree() const
{
    return _direction.AngleByAxisX() * Engine::Math::Helper::RadianToDegree + 90.f;
}

void Client::Component::SwingEffect::SetDirection(const Engine::Math::Vector2& direction)
{
    _direction = direction;
}
