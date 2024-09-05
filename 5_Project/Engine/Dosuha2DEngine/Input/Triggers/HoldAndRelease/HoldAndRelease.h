#pragma once

namespace Input::Trigger
{
    class HoldAndRelease : public Trigger, public IHoldAndRelease
    {
    public:
        void Update(float deltaTime) override;
    };
}
