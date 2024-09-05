#include "pch.h"
#include "FadeBitmapComponent.h"

Engine::Component::FadeBitmap::FadeBitmap(std::wstring path)
    : AlphaBitmap(std::move(path)), _duration(0.5f), _elapsedTime(_opacity), _state(State::None)
{
}

void Engine::Component::FadeBitmap::Update(const float deltaMetaTime, const float deltaGameTime)
{
    AlphaBitmap::Update(deltaMetaTime, deltaGameTime);
    UpdateFade(deltaMetaTime);
}

void Engine::Component::FadeBitmap::FadeIn()
{
    _state = State::FadeIn;
}

void Engine::Component::FadeBitmap::FadeOut()
{
    _state = State::FadeOut;
}

void Engine::Component::FadeBitmap::SetDuration(const float duration)
{
    _duration = duration;
}

void Engine::Component::FadeBitmap::BindOnFadeInEnd(Event event)
{
    _onFadeInEnd = std::move(event);
}

void Engine::Component::FadeBitmap::BindOnFadeOutEnd(Event event)
{
    _onFadeOutEnd = std::move(event);
}

void Engine::Component::FadeBitmap::UpdateFade(float deltaTime)
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
