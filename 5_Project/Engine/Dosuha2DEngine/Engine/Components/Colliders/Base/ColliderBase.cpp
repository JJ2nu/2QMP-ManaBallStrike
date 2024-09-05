#include "pch.h"
#include "ColliderBase.h"

Engine::Component::Collider::Base::Base(const Type type)
    : _type(type), _isActivated(true)
{
}

void Engine::Component::Collider::Base::BindOnBeginOverlap(Event onBeginOverlap)
{
    _onBeginOverlap = std::move(onBeginOverlap);
}

void Engine::Component::Collider::Base::BindOnEndOverlap(Event onEndOverlap)
{
    _onEndOverlap = std::move(onEndOverlap);
}

void Engine::Component::Collider::Base::BindOnBeginBlock(
    std::function<void(std::weak_ptr<Base>, Math::Collision::Manifold)> onBeginBlock)
{
    _onBeginBlock = std::move(onBeginBlock);
}

void Engine::Component::Collider::Base::BindOnBlock(
    std::function<void(std::weak_ptr<Base>, Math::Collision::Manifold)> onBlock)
{
    _onBlock = std::move(onBlock);
}
void Engine::Component::Collider::Base::BindOnEndBlock(Event onEndBlock)
{
    _onEndBlock = std::move(onEndBlock);
}

Engine::Component::Collider::Base::Type Engine::Component::Collider::Base::GetType() const
{
    return _isActivated ? _type : Type::NoCollision;
}

void Engine::Component::Collider::Base::Activate()
{
    _isActivated = true;
}

void Engine::Component::Collider::Base::Deactivate()
{
    _isActivated = false;
}

bool Engine::Component::Collider::Base::IsActivated() const
{
    return _isActivated;
}

void Engine::Component::Collider::Base::Reset()
{
    _previousOverlapState = std::move(_currentOverlapState);
    _currentOverlapState.clear();
    _previousBlockState = std::move(_currentBlockState);
    _currentBlockState.clear();
}

void Engine::Component::Collider::Base::InsertBlockState(std::shared_ptr<Base> other,
                                                         const Math::Collision::Manifold& manifold)
{
    _currentBlockState.insert(std::make_pair(std::move(other), manifold));
}

void Engine::Component::Collider::Base::ProcessBlock() const
{
    for (const auto& [collider, manifold] : _currentBlockState)
    {
        if (!_previousBlockState.contains(collider) && _onBeginBlock != nullptr) _onBeginBlock(collider, manifold);
        if (_onBlock != nullptr) _onBlock(collider, manifold);
    }
    for (const auto& [collider, manifold] : _previousBlockState)
    {
        if (!_currentBlockState.contains(collider) && _onEndBlock != nullptr)
            _onEndBlock(collider, manifold);
    }
}

void Engine::Component::Collider::Base::ProcessOverlap() const
{
    for (const auto& [collider, manifold] : _currentOverlapState)
    {
        if (!_previousOverlapState.contains(collider) && _onBeginOverlap != nullptr)
            _onBeginOverlap(collider, manifold);
    }
    for (const auto& [collider, manifold] : _previousOverlapState)
    {
        if (!_currentOverlapState.contains(collider) && _onEndOverlap != nullptr)
            _onEndOverlap(collider, manifold);
    }
}

void Engine::Component::Collider::Base::InsertOverlapState(std::shared_ptr<Base> other,
                                                           const Math::Collision::Manifold& manifold)
{
    _currentOverlapState.insert(std::make_pair(std::move(other), manifold));
}
