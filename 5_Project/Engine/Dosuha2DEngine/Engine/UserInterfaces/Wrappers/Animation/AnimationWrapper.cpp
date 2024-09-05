#include "pch.h"
#include "AnimationWrapper.h"

Engine::UI::Wrapper::Animation::Animation(const Math::Vector2& size, std::wstring bitmapPath,
                                          std::wstring animationPath)
    : Image(size, std::move(bitmapPath)), _animationPath(std::move(animationPath))
{
}

void Engine::UI::Wrapper::Animation::Initialize(const Manager::Resource::Loader loader)
{
    Image::Initialize(loader);
    loader->CreateAnimation(_animationPath, &_animationAsset);
}

void Engine::UI::Wrapper::Animation::Update(const float deltaMetaTime, const float deltaGameTime)
{
    _animationAsset->Update(deltaGameTime);
    Image::Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Wrapper::Animation::Render(const Manager::Render::Renderer renderer, const Math::Rect baseRect)
{
    const Math::Rect childRect = GetChildRect(baseRect);
    const Math::Rect sourceRect{_animationAsset->GetCurrentFrame().sourceRect};
    renderer->DrawBitmap(_bitmap, childRect, sourceRect);
    if (_child != nullptr) _child->Render(renderer, childRect);
}

void Engine::UI::Wrapper::Animation::Finalize()
{
    _animationAsset = nullptr;
    Image::Finalize();
}

void Engine::UI::Wrapper::Animation::SetMotion(const std::wstring& name) const
{
    _animationAsset->SetMotion(name);
}

void Engine::UI::Wrapper::Animation::BindMotionBeginEvent(const std::wstring& name,
                                                          const std::function<void()>& event) const
{
    _animationAsset->BindMotionBeginEvent(name, event);
}

void Engine::UI::Wrapper::Animation::BindMotionEndEvent(const std::wstring& name,
                                                        const std::function<void()>& event) const
{
    _animationAsset->BindMotionEndEvent(name, event);
}

void Engine::UI::Wrapper::Animation::BindFrameEvent(const std::wstring& motionName, size_t frameIndex,
                                                    const std::function<void()>& event) const
{
    _animationAsset->BindFrameEvent(motionName, frameIndex, event);
}

void Engine::UI::Wrapper::Animation::BindLastFrameEvent(const std::wstring& motionName,
                                                        const std::function<void()>& event) const
{
    _animationAsset->BindLastFrameEvent(motionName, event);
}
