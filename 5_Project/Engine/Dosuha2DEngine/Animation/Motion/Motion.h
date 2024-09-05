#pragma once
#include "../Frame/Frame.h"

namespace Animation
{
    class Motion
    {
    public:
        using Event = std::function<void()>;
        
        explicit Motion(bool isLoop);
        void AddFrame(FrameInfo&& frameInfo);
        [[nodiscard]] const FrameInfo& GetCurrentFrame() const;
        void Update(float deltaTime);
        void Reset();

        void BindBeginEvent(const Event& event);
        void BindEndEvent(const Event& event);
        void BindFrameEvent(size_t frameIndex, const Event& event);
        void BindLastFrameEvent(const Event& event);

        void ExecuteBeginEvent() const;
        void ExecuteEndEvent() const;

    private:
        float _elapsedTime;
        bool _isLoop;
        bool _isMotionEnd;
        size_t _currentFrameIndex;
        std::vector<Frame> _frames;

        Event _onBeginEvent;
        Event _onEndEvent;
    };
}
