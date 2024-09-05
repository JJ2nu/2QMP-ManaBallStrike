#include "pch.h"
#include "KnockBackMovement.h"

Client::Component::KnockBackMovement::KnockBackMovement(const std::shared_ptr<Engine::Scene>& movableScene)
    : Movement(movableScene), _isKnockBack(false), _knockBackDirection(Engine::Math::Vector2::Zero()),
      _knockBackDuration(Manager::Config::GetSection(L"Gimic")->GetFloat(L"KnockBackDuration")),
      _knockBackElapsedTime(0.f),
      _knockBackSpeedRatio(Manager::Config::GetSection(L"Gimic")->GetFloat(L"KnockBackSpeedRatio"))
{
}

void Client::Component::KnockBackMovement::Update(const float deltaMetaTime, const float deltaGameTime)
{
    if (_isKnockBack) UpdateKnockBack(deltaGameTime);
    else Movement::Update(deltaMetaTime, deltaGameTime);
}

void Client::Component::KnockBackMovement::KnockBack(const Engine::Math::Vector2& direction)
{
    if (_isKnockBack) return;
    _knockBackDirection = direction;
    _knockBackElapsedTime = 0;
    _isKnockBack = true;
}

void Client::Component::KnockBackMovement::UpdateKnockBack(const float deltaTime)
{
    _knockBackElapsedTime += deltaTime;
    if (_knockBackElapsedTime <= _knockBackDuration)
        _movableScene->SetLocation(
            _movableScene->GetLocation() + _knockBackDirection * (_speed * _knockBackSpeedRatio * deltaTime));
    else
        _isKnockBack = false;
}
