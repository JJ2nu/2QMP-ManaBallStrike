#include "pch.h"
#include "Collisionable.h"

Engine::Collisionable::Collisionable()
    : _willRelease(false)
{
}

void Engine::Collisionable::Release()
{
    _willRelease = true;
}

bool Engine::Collisionable::GetWillRelease() const
{
    return _willRelease;
}
