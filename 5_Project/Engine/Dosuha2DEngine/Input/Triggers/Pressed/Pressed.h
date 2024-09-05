#pragma once

namespace Input::Trigger
{
    class Pressed : public Trigger, public IPressed
    {
    public:
        void Update(float deltaTime) override;
    };
}
