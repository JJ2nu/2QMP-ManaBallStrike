#include "pch.h"
#include "BossBackground.h"
#include "../../Components/BackgroundBitmap/BackgroundBitmap.h"

void Client::Object::BossBackground::OnCreateComponent()
{
    Background::OnCreateComponent();
    _bitmapComponent = CreateComponent<Component::BackgroundBitmap>(L"Resources/Sprites/Map/map_004.png");
    _bitmapComponent->SetParentScene(_rootScene);
    _bitmapComponent->IsRenderable = false;
}
