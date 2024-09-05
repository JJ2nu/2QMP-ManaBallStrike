#include "pch.h"
#include "CameraComponent.h"

Engine::Component::Camera::Camera(const Math::Vector2& size)
    : Camera(size, Math::Rect::Zero())
{
}

Engine::Component::Camera::Camera(const Math::Vector2& size, const Math::Rect& limit)
    : Bound(size), _limit(limit), _smoothDamp(false), _currentVelocity(0, 0), _targetPosition(0, 0), _smoothTime(0.5f)
{
}

void Engine::Component::Camera::Update(const float deltaMetaTime, const float deltaGameTime)
{
    if (_smoothDamp)
    {
        _targetPosition = GetWorldLocation();
        _location.x = Math::Helper::SmoothDamp()(_location.x, _targetPosition.x, _currentVelocity.x, _smoothTime, deltaMetaTime);
        _location.y = Math::Helper::SmoothDamp()(_location.y, _targetPosition.y, _currentVelocity.y, _smoothTime, deltaMetaTime);
    }

    UpdateTransform();
    UpdateLimitedLocation();
    UpdateBound();
}


D2D1::Matrix3x2F Engine::Component::Camera::GetCameraMatrix() const
{
    D2D1::Matrix3x2F cameraMatrix = _centerTransform * _worldTransform;
    cameraMatrix.Invert();
    return cameraMatrix;
}

const Engine::Math::Rect& Engine::Component::Camera::GetCullingBound() const
{
    return _bound;
}

void Engine::Component::Camera::SetLimit(const Math::Rect& limit)
{
    _limit = limit;
}

void Engine::Component::Camera::SetSmoothDamp(bool value)
{
    _smoothDamp = value;
}

void Engine::Component::Camera::SetSmoothTime(float smoothTime)
{
    _smoothTime = smoothTime;
}

void Engine::Component::Camera::UpdateWorldTransform()
{
    _scaleMatrix = D2D1::Matrix3x2F::Scale(_scale);
    _rotationMatrix = D2D1::Matrix3x2F::Rotation(_rotation);
    _translationMatrix = D2D1::Matrix3x2F::Translation(_location);
    _transform = _scaleMatrix * _rotationMatrix * _translationMatrix;
    if (_parentScene.expired()) _worldTransform = _transform;
    else _worldTransform = _transform * _parentScene.lock()->GetTranslationMatrix();
}

void Engine::Component::Camera::UpdateLimitedLocation()
{
    if (_limit == Math::Rect::Zero()) return;
    const Math::Vector2 extent = _size / 2;
    const Math::Vector2 worldLocation = GetWorldLocation();
    const Math::Vector2 minLocation = _limit.GetMin() + extent;
    const Math::Vector2 maxLocation = _limit.GetMax() - extent;
    Math::Vector2 deltaLocation = Math::Vector2::Zero();
    if (worldLocation.x < minLocation.x) deltaLocation.x = minLocation.x - worldLocation.x;
    else if (worldLocation.x > maxLocation.x) deltaLocation.x = maxLocation.x - worldLocation.x;
    if (worldLocation.y < minLocation.y) deltaLocation.y = minLocation.y - worldLocation.y;
    else if (worldLocation.y > maxLocation.y) deltaLocation.y = maxLocation.y - worldLocation.y;
    _worldTransform = _worldTransform * D2D1::Matrix3x2F::Translation(deltaLocation);
}
