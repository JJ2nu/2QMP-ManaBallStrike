#include "pch.h"
#include "FadeImageWrapper.h"

Engine::UI::Wrapper::FadeImage::FadeImage(const Math::Vector2& size, std::wstring path)
    : Image(size, std::move(path)), _opacity(0.0f), _duration(0.5f), _elapsedTime(0), _state(State::None)
{
    
}

void Engine::UI::Wrapper::FadeImage::FadeIn()
{
    _state = State::FadeIn;
}

void Engine::UI::Wrapper::FadeImage::FadeOut()
{
    _state = State::FadeOut;
}

void Engine::UI::Wrapper::FadeImage::Update(float deltaMetaTime, float deltaGameTime)
{
    UpdateFade(deltaMetaTime);
    Image::Update(deltaMetaTime, deltaGameTime);
}

void Engine::UI::Wrapper::FadeImage::Render(const Manager::Render::Renderer renderer, const Math::Rect baseRect)
{
    const Math::Rect childRect = GetChildRect(baseRect);
    renderer->DrawBitmap(_bitmap, childRect, _opacity);
    if (_child != nullptr) _child->Render(renderer, childRect);
}

void Engine::UI::Wrapper::FadeImage::SetDuration(float duration)
{
    _duration = duration;
}

void Engine::UI::Wrapper::FadeImage::SetOpacity(float opacity)
{
    _opacity = opacity;
}

void Engine::UI::Wrapper::FadeImage::BindOnFadeInEnd(Event event)
{
    _onFadeInEnd = std::move(event);
}

void Engine::UI::Wrapper::FadeImage::BindOnFadeOutEnd(Event event)
{
    _onFadeOutEnd = std::move(event);
}

void Engine::UI::Wrapper::FadeImage::Reset()
{
    _opacity = 0.0f;
    _elapsedTime = 0.0f;
    _state = State::None;
}

void Engine::UI::Wrapper::FadeImage::UpdateFade(float deltaTime)
{
    if (_state == State::None) return;
    float time = 0;
    if (_state == State::FadeIn)
    {
        _elapsedTime += deltaTime;
        time = Math::Helper::Min()(_elapsedTime / _duration, 1.f);
        if (time == 1.f)
        {
            _state = State::None;
            if (_onFadeInEnd) _onFadeInEnd();
        }
    }
    else if (_state == State::FadeOut)
    {
        _elapsedTime -= deltaTime;
        time = Math::Helper::Max()(_elapsedTime / _duration, 0.f);
        if (time == 0.f)
        {
            _state = State::None;
            if (_onFadeOutEnd) _onFadeOutEnd();
        }
    }
    _opacity = Math::Helper::Lerp()(0.f, 1.f, time);
}
