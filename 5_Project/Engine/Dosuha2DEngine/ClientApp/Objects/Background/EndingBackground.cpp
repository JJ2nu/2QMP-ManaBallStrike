#include "pch.h"
#include "Components/BackgroundBitmap/BackgroundBitmap.h"
#include "EndingBackground.h"


Client::Object::EndingBackground::EndingBackground()
{
    AddTag(L"EndingBackground");
}

const Engine::Math::Rect& Client::Object::EndingBackground::GetBound() const
{
    return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::EndingBackground::GetColliders() const
{
    return { _boxCollider };
}

void Client::Object::EndingBackground::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _boxCollider = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Overlap,
        Engine::Math::Vector2{ 1580, 1060 });
    _boxCollider->SetParentScene(_rootScene);

    _bitmapComponent = CreateComponent<Client::Component::BackgroundBitmap>(L"Resources/Sprites/Map/space_earth.png");
    _bitmapComponent->SetParentScene(_rootScene);
    _bitmapComponent->IsRenderable = false;
}

void Client::Object::EndingBackground::OnSetup()
{
    _bitmapComponent->SetBackgroundBitmap();
    _boundComponent->SetSize(_bitmapComponent->GetSize());
}
