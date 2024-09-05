#include "pch.h"
#include "AutoMovePlayer.h"

#include "Components/EventBindAnimation/EventBindAnimation.h"

Client::Object::AutoMovePlayer::AutoMovePlayer(const float initialYLocation)
    : PlayerBase(Engine::Math::Rect{-800, -1710, 800, 1510}, initialYLocation),
      _isLoopStop(false), _endYLocation(0.f)
{
}

void Client::Object::AutoMovePlayer::BindOnExit(Event event)
{
    _onExit = std::move(event);
}

void Client::Object::AutoMovePlayer::LoopStop()
{
    _isLoopStop = true;
    _endYLocation = _rootScene.lock()->GetLocation().y;
    _cameraComponent->SetLimit(Engine::Math::Rect{-800, _endYLocation - 650, 800, 1510});
}

void Client::Object::AutoMovePlayer::OnSetup()
{
    PlayerBase::OnSetup();
    _cameraComponent->SetLocation({0, -200});
    Move(Engine::Math::Vector2::Up());
    _animationComponent->SetMotion(L"MoveUp");
}

void Client::Object::AutoMovePlayer::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    PlayerBase::OnPostUpdate(deltaMetaTime, deltaGameTime);
    const float currentY = _rootScene.lock()->GetLocation().y;
    if (currentY < -1060 && !_isLoopStop)
    {
        _rootScene.lock()->SetLocation(Engine::Math::Vector2{0, currentY + 2120});
    }
    else if (_isLoopStop && currentY < _endYLocation - 700)
    {
        if (_onExit != nullptr) _onExit();
    }
}
