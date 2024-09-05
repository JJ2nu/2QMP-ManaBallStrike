#pragma once
#include "../../Component/Button/Button.h"
#include "../../Component/Axis/Axis.h"


namespace Input::Device
{
    class Mouse : public IMouse
    {
    public:
        Mouse();

        void SetHandle(HWND handle) override;

        void Update() override;
        void Reset() override;

        Component::IComponent* GetComponent(Button button) override;
        Component::IComponent* GetComponent(Axis axis) override;

        [[nodiscard]] Value GetPosition() const override;

    private:
        void UpdateAxis();
        void UpdateButton();

        HWND _handle;

        std::unordered_map<Axis, Component::Axis> _axes;
        std::unordered_map<Button, Component::Button> _buttons;
    };
}
