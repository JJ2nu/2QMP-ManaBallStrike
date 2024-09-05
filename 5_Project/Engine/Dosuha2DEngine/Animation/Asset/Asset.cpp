#include "pch.h"
#include "Asset.h"

Animation::Asset::Asset()
    : _referenceCount(1)
{
}

void Animation::Asset::AddReference()
{
    ++_referenceCount;
}

long Animation::Asset::Release()
{
    if (--_referenceCount > 0) return _referenceCount;
    delete this;
    return 0;
}

void Animation::Asset::Update(const float deltaTime)
{
    _motions.at(_currentMotionName).Update(deltaTime);
}

void Animation::Asset::LoadMotion(const std::wstring& name, bool loop, const std::wstring& path)
{
    ThrowRuntimeErrorIf<Exception::RuntimeException>()(_motions.contains(name), L"Motion already exists: " + name);
    auto [pair, _] = _motions.emplace(name, Motion(loop));
    std::wifstream file(path);
    ThrowRuntimeErrorIf<Exception::RuntimeException>()(!file.is_open(), L"Failed to open file: " + path);
    std::wstring line;
    size_t frameCount = 0;
    {
        std::getline(file, line);
        std::wstringstream wss(line);
        wss >> frameCount;
    }
    for (size_t i = 0; i < frameCount; ++i)
    {
        std::getline(file, line);
        {
            std::wstringstream wss(line);
            std::wstring token;
            std::getline(wss, token, L',');
            float left = std::stof(token);
            std::getline(wss, token, L',');
            float top = std::stof(token);
            std::getline(wss, token, L',');
            float right = std::stof(token);
            std::getline(wss, token, L',');
            float bottom = std::stof(token);
            std::getline(wss, token, L',');
            float x = std::stof(token);
            std::getline(wss, token, L',');
            float y = std::stof(token);
            std::getline(wss, token, L',');
            float duration = std::stof(token);
            pair->second.AddFrame(FrameInfo{SourceRect{left, top, right, bottom}, Center{x, y}, duration});
        }
    }
    _currentMotionName = name;
}

const Animation::FrameInfo& Animation::Asset::GetCurrentFrame() const
{
    return _motions.at(_currentMotionName).GetCurrentFrame();
}

void Animation::Asset::SetMotion(const std::wstring& name)
{
    ThrowRuntimeErrorIf<Exception::RuntimeException>()(!_motions.contains(name), L"Motion not found: " + name);
    _motions.at(_currentMotionName).ExecuteEndEvent();
    _motions.at(_currentMotionName).Reset();
    _currentMotionName = name;
    _motions.at(_currentMotionName).ExecuteBeginEvent();
}

void Animation::Asset::BindMotionBeginEvent(const std::wstring& name, const std::function<void()>& event)
{
    _motions.at(name).BindBeginEvent(event);
}

void Animation::Asset::BindMotionEndEvent(const std::wstring& name, const std::function<void()>& event)
{
    _motions.at(name).BindEndEvent(event);
}

void Animation::Asset::BindFrameEvent(const std::wstring& motionName, const size_t frameIndex,
                                      const std::function<void()>& event)
{
    _motions.at(motionName).BindFrameEvent(frameIndex, event);
}

void Animation::Asset::BindLastFrameEvent(const std::wstring& motionName, const std::function<void()>& event)
{
    _motions.at(motionName).BindLastFrameEvent(event);
}
