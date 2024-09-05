#pragma once

namespace Input::Trigger
{
    class Tap : public Trigger, public ITap
    {
    public:
        void Update(float deltaTime) override;
    };
}
