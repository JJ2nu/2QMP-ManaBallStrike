#include "pch.h"
#include "Components/BackgroundBitmap/BackgroundBitmap.h"
#include "Background.h"


Client::Object::Background::Background()
{
    AddTag(L"Background");
}

const Engine::Math::Rect& Client::Object::Background::GetBound() const
{
    return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::Background::GetColliders() const
{
    return {_boxCollider};
}

void Client::Object::Background::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _boxCollider = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Overlap,
                                                                     Engine::Math::Vector2{1580, 1060});
    _boxCollider->SetParentScene(_rootScene);

    _bitmapComponent = CreateComponent<Component::BackgroundBitmap>(L"Resources/Sprites/Map/map_001.png");
    _bitmapComponent->SetParentScene(_rootScene);
    _bitmapComponent->IsRenderable = false;
}

void Client::Object::Background::OnSetup()
{
    _bitmapComponent->SetBackgroundBitmap();
    _boundComponent->SetSize(_bitmapComponent->GetSize());
}
