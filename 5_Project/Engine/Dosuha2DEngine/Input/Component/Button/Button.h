#pragma once

namespace Input::Component
{
    class Button : public IComponent
    {
    public:
        Button();

        void SetValue(bool value);
        [[nodiscard]] Value GetValue() const override;
        void Reset() override;

    private:
        bool _value;
    };
}
