#include "pch.h"
#include "Scene.h"

Engine::Scene::Scene()
    : _location(Math::Vector2::Zero()), _rotation(0), _scale(Math::Vector2::One()), _center(Math::Vector2::Half()),
      _translationMatrix(D2D1::Matrix3x2F::Identity()), _rotationMatrix(D2D1::Matrix3x2F::Identity()),
      _scaleMatrix(D2D1::Matrix3x2F::Identity()), _transform(D2D1::Matrix3x2F::Identity()),
      _worldTransform(D2D1::Matrix3x2F::Identity()),
      _centerTransform(D2D1::Matrix3x2F::Identity())
{
}

void Engine::Scene::SetParentScene(const std::weak_ptr<Scene>& parent)
{
    _parentScene = parent;
}

Engine::Math::Vector2 Engine::Scene::GetLocation() const
{
    return _location;
}

float Engine::Scene::GetRotation() const
{
    return _rotation;
}

void Engine::Scene::SetLocation(const Math::Vector2& location)
{
    _location = location;
}

void Engine::Scene::SetRotation(const float rotation)
{
    _rotation = rotation;
}

Engine::Math::Vector2 Engine::Scene::GetScale() const
{
    return _scale;
}

void Engine::Scene::SetScale(const Math::Vector2& scale)
{
    _scale = scale;
}

void Engine::Scene::SetCenter(const Math::Vector2& center)
{
    _center = center;
}

D2D1::Matrix3x2F Engine::Scene::GetWorldTransform() const noexcept
{
    return _worldTransform;
}

D2D1::Matrix3x2F Engine::Scene::GetCenterTransform() const noexcept
{
    return _centerTransform;
}

D2D1::Matrix3x2F Engine::Scene::GetTranslationMatrix() const noexcept
{
    return _translationMatrix;
}

Engine::Math::Vector2 Engine::Scene::GetWorldLocation() const
{
    return {_worldTransform.dx, _worldTransform.dy};
}

void Engine::Scene::UpdateTransform()
{
    UpdateCenterTransform();
    UpdateWorldTransform();
}

void Engine::Scene::UpdateWorldTransform()
{
    _scaleMatrix = D2D1::Matrix3x2F::Scale(_scale);
    _rotationMatrix = D2D1::Matrix3x2F::Rotation(_rotation);
    _translationMatrix = D2D1::Matrix3x2F::Translation(_location);
    _transform = _scaleMatrix * _rotationMatrix * _translationMatrix;
    if (_parentScene.expired()) _worldTransform = _transform;
    else _worldTransform = _transform * _parentScene.lock()->_worldTransform;
}
