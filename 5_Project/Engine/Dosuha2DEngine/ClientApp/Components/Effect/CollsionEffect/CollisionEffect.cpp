#include "pch.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"
#include "CollisionEffect.h"
Client::Component::CollisionEffect::CollisionEffect(std::wstring path, std::wstring motion)
    :EventBindAnimation(path,motion)
{
}

void Client::Component::CollisionEffect::Update(float deltaMetaTime, float deltaGameTime)
{
    //float degree = GetDegree();
    //SetRotation(degree);
    EventBindAnimation::Update(deltaMetaTime, deltaGameTime);
}

float Client::Component::CollisionEffect::GetDegree()
{
    //D2D1::Matrix3x2F cameraMatrix = Engine::Manager::Camera::GetCameraMatrix();
    //cameraMatrix.Invert();
    //const Engine::Math::Vector2 direction
    //    = CollisionPoint- GetWorldLocation();
    return CollisionDegree.AngleByAxisX() * Engine::Math::Helper::RadianToDegree +90.f;
}
void Client::Component::CollisionEffect::SetCollisionPoint(const Engine::Math::Vector2& point)
{
    CollisionPoint = point;
    SetRotation(GetDegree());
}

void Client::Component::CollisionEffect::SetCollisionDegree(const Engine::Math::Vector2& rotation)
{
    CollisionDegree = rotation;
    SetRotation(GetDegree());
}
