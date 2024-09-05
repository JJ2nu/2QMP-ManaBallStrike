#pragma once

namespace Input::Trigger
{
    class Released : public Trigger, public IReleased
    {
    public:
        void Update(float deltaTime) override;
    };
}
