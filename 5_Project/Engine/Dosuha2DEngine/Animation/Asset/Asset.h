#pragma once
#include "../Motion/Motion.h"

namespace Animation
{
    class Asset : public IAsset
    {
    public:
        Asset();

        void AddReference() override;
        long Release() override;

        void Update(float deltaTime) override;

        void LoadMotion(const std::wstring& name, bool loop, const std::wstring& path);
        [[nodiscard]] const FrameInfo& GetCurrentFrame() const override;
        void SetMotion(const std::wstring& name) override;

        void BindMotionBeginEvent(const std::wstring& name, const std::function<void()>& event) override;
        void BindMotionEndEvent(const std::wstring& name, const std::function<void()>& event) override;
        void BindFrameEvent(const std::wstring& motionName, size_t frameIndex, const std::function<void()>& event) override;
        void BindLastFrameEvent(const std::wstring& motionName, const std::function<void()>& event) override;

    private:
        std::atomic<long> _referenceCount;

        std::wstring _currentMotionName;
        std::unordered_map<std::wstring, Motion> _motions;
    };
}
