#include "pch.h"
#include "Stroked.h"

Engine::Stroked::Stroked(const float strokeWidth)
    : _strokeWidth(strokeWidth)
{
}

void Engine::Stroked::SetStrokeWidth(const float strokeWidth)
{
    _strokeWidth = strokeWidth;
}
