#pragma once

namespace Input::Component
{
    class Axis : public IComponent
    {
    public:
        Axis();

        void SetValue(long value);
        [[nodiscard]] Value GetValue() const override;
        [[nodiscard]] long GetValueRaw() const ;
        void Reset() override;

        void SetDeadZone(float deadZone);
        void SetSensitivity(long sensitivity);

    private:
        long _value;
        long _sensitivity;
        float _deadZone;
    };
}
