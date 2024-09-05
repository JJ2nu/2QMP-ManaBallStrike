#include "pch.h"
#include "Motion.h"

Animation::Motion::Motion(const bool isLoop)
    : _elapsedTime(0.f), _isLoop(isLoop), _isMotionEnd(false), _currentFrameIndex(0), _onBeginEvent(nullptr),
      _onEndEvent(nullptr)
{
}

void Animation::Motion::AddFrame(FrameInfo&& frameInfo)
{
    _frames.emplace_back(std::forward<FrameInfo>(frameInfo));
}

const Animation::FrameInfo& Animation::Motion::GetCurrentFrame() const
{
    return _frames[_currentFrameIndex].GetFrameInfo();
}

void Animation::Motion::Update(const float deltaTime)
{
    if (_isMotionEnd) return;
    _elapsedTime += deltaTime;
    const float duration = _frames[_currentFrameIndex].GetFrameInfo().duration;
    while (_elapsedTime >= duration)
    {
        _elapsedTime -= duration;
        ++_currentFrameIndex;
        if (_currentFrameIndex == _frames.size())
        {
            if (_isLoop) _currentFrameIndex = 0;
            else
            {
                --_currentFrameIndex;
                _isMotionEnd = true;
                break;
            }
        }
        _frames[_currentFrameIndex].ExecuteEvent();
    }
}

void Animation::Motion::Reset()
{
    _elapsedTime = 0;
    _currentFrameIndex = 0;
    _isMotionEnd = false;
    _frames[_currentFrameIndex].ExecuteEvent();
}

void Animation::Motion::BindBeginEvent(const Event& event)
{
    _onBeginEvent = event;
}

void Animation::Motion::BindEndEvent(const Event& event)
{
    _onEndEvent = event;
}

void Animation::Motion::BindFrameEvent(const size_t frameIndex, const Event& event)
{
    _frames[frameIndex].BindEvent(event);
}

void Animation::Motion::BindLastFrameEvent(const Event& event)
{
    _frames.back().BindEvent(event);
}

void Animation::Motion::ExecuteBeginEvent() const
{
    if (_onBeginEvent) _onBeginEvent();
}

void Animation::Motion::ExecuteEndEvent() const
{
    if (_onEndEvent) _onEndEvent();
}