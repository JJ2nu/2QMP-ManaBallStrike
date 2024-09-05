#include "pch.h"
#include "DashMovement.h"

Client::Component::DashMovement::DashMovement(const std::shared_ptr<Engine::Scene>& movableScene)
    : KnockBackMovement(movableScene), _dashDuration{}, _elapsedTime(0.f), _speedRatio{},
      _dashDirection(Engine::Math::Vector2::Zero()), _isDashing(false), _dashCoolTime{}, _isCooling(false)
{
    auto playerSection = Manager::Config::GetSection(L"Player");
    _speedRatio = playerSection->GetFloat(L"DashSpeedRatio");
    _dashDuration = playerSection->GetFloat(L"DashDuration");
    _dashCoolTime = playerSection->GetFloat(L"CoolTime");
}

void Client::Component::DashMovement::Update(const float deltaMetaTime, const float deltaGameTime)
{
    UpdateColling(deltaGameTime);
    UpdateDash(deltaGameTime);
    KnockBackMovement::Update(deltaMetaTime, deltaGameTime);
}

bool Client::Component::DashMovement::Dash()
{
    if (_isDashing || _isCooling) return false;
    _dashDirection = _direction;
    _elapsedTime = 0;
    _isDashing = true;
    return true;
}

bool Client::Component::DashMovement::IsDashing() const
{
    return _isDashing;
}

void Client::Component::DashMovement::UpdateColling(float deltaTime)
{
    if (!_isCooling) return;
    _elapsedTime += deltaTime;
    if (_elapsedTime >= _dashCoolTime)
    {
        _isCooling = false;
        _elapsedTime = 0;
    }
}

void Client::Component::DashMovement::UpdateDash(const float deltaTime)
{
    if (!_isDashing) return;
    _elapsedTime += deltaTime;
    if (_elapsedTime <= _dashDuration)
        _movableScene->SetLocation(
            _movableScene->GetLocation() + _dashDirection * (_speed * _speedRatio * deltaTime));
    else
    {
        _isDashing = false;
        _isCooling = true;
        _elapsedTime = 0;
    }
}
