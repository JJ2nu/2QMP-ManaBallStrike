#include "pch.h"
#include "ImageWrapper.h"

Engine::UI::Wrapper::Image::Image(std::wstring path)
    : Image(Math::Vector2::Zero(), std::move(path))
{
}

Engine::UI::Wrapper::Image::Image(const Math::Vector2& size, std::wstring path)
    : Base(size), _path(std::move(path))
{
}

void Engine::UI::Wrapper::Image::Initialize(const Manager::Resource::Loader loader)
{
    loader->CreateBitmap(_path, &_bitmap);
    if (_size == Math::Vector2::Zero()) _size = Math::Vector2(_bitmap->GetSize());
}

void Engine::UI::Wrapper::Image::Render(const Manager::Render::Renderer renderer, const Math::Rect baseRect)
{
    const Math::Rect childRect = GetChildRect(baseRect);
    renderer->DrawBitmap(_bitmap, childRect);
    if (_child != nullptr) _child->Render(renderer, childRect);
}

void Engine::UI::Wrapper::Image::Finalize()
{
    _bitmap = nullptr;
}
