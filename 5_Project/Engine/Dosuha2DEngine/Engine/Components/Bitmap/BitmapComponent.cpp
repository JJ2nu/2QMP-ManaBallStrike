#include "pch.h"
#include "BitmapComponent.h"

void Engine::Component::Bitmap::Initialize(const Manager::Resource::Loader loader)
{
    loader->CreateBitmap(_bitmapPath, &_bitmap);
}

Engine::Component::Bitmap::Bitmap(std::wstring path)
    : _bitmapPath(std::move(path))
{
}

void Engine::Component::Bitmap::Update(float deltaMetaTime, float deltaGameTime)
{
    UpdateTransform();
}

void Engine::Component::Bitmap::Render(const Manager::Render::Renderer renderer,
                                       const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _worldTransform * cameraMatrix);
    renderer->DrawBitmap(_bitmap);
}



void Engine::Component::Bitmap::Finalize()
{
    _bitmap = nullptr;
}

Engine::Math::Vector2 Engine::Component::Bitmap::GetSize() const
{
    return _bitmap->GetSize();
}

void Engine::Component::Bitmap::UpdateCenterTransform()
{
    _centerTransform = D2D1::Matrix3x2F::Translation(-1 * Math::Vector2::SplitProduct(_bitmap->GetSize(), _center));
}
