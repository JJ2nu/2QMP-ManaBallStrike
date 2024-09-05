#include "pch.h"
#include "CameraObject.h"

Engine::Object::Camera::Camera(const Math::Vector2& size)
    : _size(size)
{

}

D2D1::Matrix3x2F Engine::Object::Camera::GetCameraMatrix() const
{
    return _cameraComponent->GetCameraMatrix();
}

const Engine::Math::Rect& Engine::Object::Camera::GetCullingBound() const
{
    return _cameraComponent->GetCullingBound();
}

const Engine::Math::Rect& Engine::Object::Camera::GetBound() const
{
    return _cameraComponent->GetCullingBound();
}

void Engine::Object::Camera::OnCreateComponent()
{
    _cameraComponent = CreateComponent<Component::Camera>(_size);
    SetRootScene(_cameraComponent);
}
