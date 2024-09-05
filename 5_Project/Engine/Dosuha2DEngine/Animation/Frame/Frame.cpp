#include "pch.h"
#include "Frame.h"

Animation::Frame::Frame(const FrameInfo& frameInfo)
    : _frameInfo(frameInfo)
{
}

const Animation::FrameInfo& Animation::Frame::GetFrameInfo() const
{
    return _frameInfo;
}

void Animation::Frame::BindEvent(const Event& event)
{
    _event = event;
}

void Animation::Frame::ExecuteEvent() const
{
    if (_event) _event();
}
