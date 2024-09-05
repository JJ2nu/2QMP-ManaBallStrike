#pragma once
#include "../../Component/Button/Button.h"
#include "../../Component/Axis/Axis.h"

namespace Input::Device
{
    class Controller : public IController
    {
        static constexpr DWORD Disconnection = -1;
        static constexpr float ThumbDefaultDeadZone = 0.2f;
        static constexpr long ThumbStickSensitive = 32767;
        static constexpr long TriggerSensitive = 255;
        static constexpr unsigned short VibrationSensitive = 65535;

    public:
        Controller();

        void Update() override;
        void Reset() override;

        Component::IComponent* GetComponent(Button button) override;
        Component::IComponent* GetComponent(Trigger trigger) override;
        Component::IComponent* GetComponent(Thumb thumb) override;
        void StartVibration(float intensity) override;
        void StartVibration(Vibration vibration, float intensity) override;
        void StopVibration() override;

    private:
        static unsigned short GetFlag(Button button);
        
        bool CheckConnection();

        DWORD _controllerIndex;

        std::unordered_map<Button, Component::Button> _buttons;
        std::unordered_map<Trigger, Component::Axis> _triggers;
        std::unordered_map<Thumb, Component::Axis> _thumbs;
    };
}
