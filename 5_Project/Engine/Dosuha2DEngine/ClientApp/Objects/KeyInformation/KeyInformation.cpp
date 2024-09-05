#include "pch.h"
#include "KeyInformation.h"

void Client::Object::KeyInformation::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _bitmapComponent = CreateComponent<Engine::Component::Bitmap>(L"Resources/Sprites/Map/map_001_01.png");
    _bitmapComponent->SetParentScene(_rootScene);
}

void Client::Object::KeyInformation::OnSetup()
{
    _renderOrder = 0;
    _rootScene.lock()->SetLocation(Engine::Math::Vector2{0,200});
}

const Engine::Math::Rect& Client::Object::KeyInformation::GetBound() const
{
    return _boundComponent->GetBound();
}
