#include "pch.h"
#include "MovementComponent.h"

Engine::Component::Movement::Movement(const std::shared_ptr<Scene>& movableScene)
    : Movement(movableScene, 0.0f)
{
}

Engine::Component::Movement::Movement(const std::shared_ptr<Scene>& movableScene, const float speed)
    : _movableScene(movableScene), _speed(speed), _direction(Math::Vector2::Zero())
{
}

void Engine::Component::Movement::Update(float deltaMetaTime, const float deltaGameTime)
{
    _movableScene->SetLocation(_movableScene->GetLocation() + _direction * (_speed * deltaGameTime));
}

void Engine::Component::Movement::SetSpeed(const float speed)
{
    _speed = speed;
}

void Engine::Component::Movement::SetDirection(const Math::Vector2& direction)
{
    _direction = direction.Normalize();
}

Engine::Math::Vector2 Engine::Component::Movement::GetDirection() const
{
    return _direction;
}
