#pragma once

namespace Animation
{
    class Frame
    {
    public:
        using Event = std::function<void()>;
        
        explicit Frame(const FrameInfo& frameInfo);

        [[nodiscard]] const FrameInfo& GetFrameInfo() const;

        void BindEvent(const Event& event);
        void ExecuteEvent() const;

    private:
        FrameInfo _frameInfo;
        Event _event;
    };
}
