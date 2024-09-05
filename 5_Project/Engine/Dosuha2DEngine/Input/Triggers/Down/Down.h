#pragma once

namespace Input::Trigger
{
    class Down : public Trigger, public IDown
    {
    public:
        Down() = default;

        void Update(float deltaTime) override;

    private:
        bool _isDown;
    };
}
