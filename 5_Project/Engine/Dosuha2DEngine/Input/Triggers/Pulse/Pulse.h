#pragma once

namespace Input::Trigger
{
    class Pulse : public Trigger, public IPulse
    {
    public:
        void Update(float deltaTime) override;
    };
};
