#include "pch.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"
#include "TrailEffect.h"
Client::Component::TrailEffect::TrailEffect(std::wstring path, std::wstring motion)
    :EventBindAnimation(path, motion)
{
}