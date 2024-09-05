#pragma once

namespace Animation
{
    struct IAsset : Dosuha::IReferenceCounter
    {
        virtual void Update(float deltaTime) = 0;
        [[nodiscard]] virtual const FrameInfo& GetCurrentFrame() const = 0;
        virtual void SetMotion(const std::wstring& name) = 0;
        virtual void BindMotionBeginEvent(const std::wstring& name, const std::function<void()>& event) = 0;
        virtual void BindMotionEndEvent(const std::wstring& name, const std::function<void()>& event) = 0;
        virtual void BindFrameEvent(const std::wstring& motionName, size_t frameIndex, const std::function<void()>& event) = 0;
        virtual void BindLastFrameEvent(const std::wstring& motionName, const std::function<void()>& event) = 0;
    };
}
