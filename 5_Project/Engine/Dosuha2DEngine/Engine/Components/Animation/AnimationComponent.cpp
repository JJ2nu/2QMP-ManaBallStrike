#include "pch.h"
#include "AnimationComponent.h"

Engine::Component::Animation::Animation(const std::wstring& bitmapPath, const std::wstring& animationPath)
    : Bitmap(bitmapPath), _animationPath(animationPath), _isMirror(false), _mirrorMatrix(D2D1::Matrix3x2F::Identity())
{
}

void Engine::Component::Animation::Initialize(const Manager::Resource::Loader loader)
{
    Bitmap::Initialize(loader);
    loader->CreateAnimation(_animationPath, &_animationAsset);
}

void Engine::Component::Animation::Update(const float deltaMetaTime, const float deltaGameTime)
{
    _animationAsset->Update(deltaGameTime);
    Bitmap::Update(deltaMetaTime, deltaGameTime);
    UpdateMirrorMatrix();
}

void Engine::Component::Animation::Render(const Manager::Render::Renderer renderer,
                                          const D2D1_MATRIX_3X2_F cameraMatrix) const
{
    renderer->SetTransform(_centerTransform * _mirrorMatrix * _worldTransform * cameraMatrix);
    const Math::Rect sourceRect {_animationAsset->GetCurrentFrame().sourceRect};
    renderer->DrawBitmap(_bitmap, Math::Rect{0, 0, sourceRect.GetSize().x, sourceRect.GetSize().y}, sourceRect);
}

void Engine::Component::Animation::Finalize()
{
    _animationAsset = nullptr;
    Bitmap::Finalize();
}

void Engine::Component::Animation::SetMirror(bool isMirror)
{
    _isMirror = isMirror;
}

void Engine::Component::Animation::SetMotion(const std::wstring& name) 
{
    _animationAsset->SetMotion(name);
    UpdateCenterTransform();
}


void Engine::Component::Animation::UpdateCenterTransform()
{
    _centerTransform = D2D1::Matrix3x2F::Translation(-1 * Math::Vector2{_animationAsset->GetCurrentFrame().center});
}

void Engine::Component::Animation::UpdateMirrorMatrix()
{
    _mirrorMatrix = _isMirror ? D2D1::Matrix3x2F::Scale(-1, 1) : D2D1::Matrix3x2F::Identity();
}
