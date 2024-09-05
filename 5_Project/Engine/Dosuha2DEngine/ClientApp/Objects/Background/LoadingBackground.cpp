#include "pch.h"
#include "LoadingBackground.h"
#include "Components/BackgroundBitmap/BackgroundBitmap.h"

Client::Object::LoadingBackground::LoadingBackground(const float initialYLocation)
    : _initialYLocation(initialYLocation)
{
}

const Engine::Math::Rect& Client::Object::LoadingBackground::GetBound() const
{
    return _boundComponent->GetBound();
}


void Client::Object::LoadingBackground::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _bitmapComponent = CreateComponent<Component::BackgroundBitmap>(L"Resources/Sprites/Map/map_003.png");
    _bitmapComponent->SetParentScene(_rootScene);
    _bitmapComponent->IsRenderable = false;
}

void Client::Object::LoadingBackground::OnSetup()
{
    _rootScene.lock()->SetLocation({0, _initialYLocation});
    _bitmapComponent->SetBackgroundBitmap();
    _boundComponent->SetSize(_bitmapComponent->GetSize());
}
