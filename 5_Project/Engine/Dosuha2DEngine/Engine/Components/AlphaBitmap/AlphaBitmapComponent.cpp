#include "pch.h"
#include "AlphaBitmapComponent.h"

Engine::Component::AlphaBitmap::AlphaBitmap(std::wstring path)
    : Bitmap(std::move(path)), _opacity(1.f)
{
}

void Engine::Component::AlphaBitmap::Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const
{
    if (_opacity > 0.f)
    {
        renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
        renderer->DrawBitmap(_bitmap, _opacity);
    }
}

void Engine::Component::AlphaBitmap::SetOpacity(const float opacity)
{
    _opacity = opacity;
}

float Engine::Component::AlphaBitmap::GetOpacity() const
{
    return _opacity;
}
