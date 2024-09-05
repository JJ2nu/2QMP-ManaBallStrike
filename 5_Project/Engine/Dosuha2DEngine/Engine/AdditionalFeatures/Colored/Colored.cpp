#include "pch.h"
#include "Colored.h"

Engine::Colored::Colored(const D2D1_COLOR_F color)
    : _color(color)
{
}

void Engine::Colored::SetColor(const D2D1_COLOR_F color)
{
    _color = color;
}
