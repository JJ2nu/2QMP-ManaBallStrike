#pragma once

namespace Input::Trigger
{
    class Hold : public Trigger, public IHold
    {
    public:
        void Update(float deltaTime) override;
    };
}
