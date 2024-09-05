#pragma once

namespace Input::Device
{
    struct IController : IDevice
    {
        enum class Vibration
        {
            Left,
            Right
        };
        enum class Button
        {
            DpadUp,
            DpadDown,
            DpadLeft,
            DpadRight,
            Start,
            Back,
            LeftThumb,
            RightThumb,
            LeftShoulder,
            RightShoulder,
            Padding1,
            Padding2,
            A,
            B,
            X,
            Y,
            Max
        };

        enum class Trigger
        {
            Left,
            Right,
            Max
        };

        enum class Thumb
        {
            LeftX,
            LeftY,
            RightX,
            RightY,
            Max
        };

        virtual Component::IComponent* GetComponent(Button button) = 0;
        virtual Component::IComponent* GetComponent(Trigger trigger) = 0;
        virtual Component::IComponent* GetComponent(Thumb thumb) = 0;
        virtual void StartVibration(float intensity) = 0;
        virtual void StartVibration(Vibration vibration, float intensity) = 0;
        virtual void StopVibration() = 0;
    };
}
