#include "pch.h"
#include "Controller.h"

Input::Device::Controller::Controller()
    : _controllerIndex(Disconnection), _buttons(static_cast<size_t>(Button::Max)),
      _triggers(static_cast<size_t>(Trigger::Max)), _thumbs(static_cast<size_t>(Thumb::Max))
{
    std::ranges::for_each(_triggers, [](auto& trigger) { trigger.second.SetSensitivity(TriggerSensitive); });
    std::ranges::for_each(_thumbs, [](auto& thumb)
    {
        thumb.second.SetSensitivity(ThumbStickSensitive);
        thumb.second.SetDeadZone(ThumbDefaultDeadZone);
    });
}

void Input::Device::Controller::Update()
{
    if (_controllerIndex == Disconnection && CheckConnection()) return;
    XINPUT_STATE state{};
    if (XInputGetState(_controllerIndex, &state) != ERROR_SUCCESS)
    {
        _controllerIndex = Disconnection;
        return;
    }

    _triggers[Trigger::Left].SetValue(state.Gamepad.bLeftTrigger);
    _triggers[Trigger::Right].SetValue(state.Gamepad.bRightTrigger);

    _thumbs[Thumb::LeftX].SetValue(state.Gamepad.sThumbLX);
    _thumbs[Thumb::LeftY].SetValue(state.Gamepad.sThumbLY);
    _thumbs[Thumb::RightX].SetValue(state.Gamepad.sThumbRX);
    _thumbs[Thumb::RightY].SetValue(state.Gamepad.sThumbRY);

    for (unsigned short button = 0; button < static_cast<unsigned short>(Button::Max); ++button)
    {
        _buttons[static_cast<Button>(button)].SetValue(GetFlag(static_cast<Button>(button)) & state.Gamepad.wButtons);
    }
}

void Input::Device::Controller::Reset()
{
    std::ranges::for_each(_buttons, [](auto& button) { button.second.Reset(); });
    std::ranges::for_each(_triggers, [](auto& trigger) { trigger.second.Reset(); });
    std::ranges::for_each(_thumbs, [](auto& thumb) { thumb.second.Reset(); });
}

Input::Component::IComponent* Input::Device::Controller::GetComponent(const Button button)
{
    return &_buttons[button];
}

Input::Component::IComponent* Input::Device::Controller::GetComponent(const Trigger trigger)
{
    return &_triggers[trigger];
}

Input::Component::IComponent* Input::Device::Controller::GetComponent(const Thumb thumb)
{
    return &_thumbs[thumb];
}

void Input::Device::Controller::StartVibration(const float intensity)
{
    const WORD motorSpeed = static_cast<WORD>(VibrationSensitive * intensity);
    XINPUT_VIBRATION vibration{ motorSpeed, motorSpeed};
    XInputSetState(_controllerIndex, &vibration);
}

void Input::Device::Controller::StartVibration(Vibration vibration, float intensity)
{
    const WORD motorSpeed = static_cast<WORD>(VibrationSensitive * intensity);
    XINPUT_VIBRATION xInputVibration;
    switch (vibration)
    {
    case Vibration::Left:
        xInputVibration.wLeftMotorSpeed = motorSpeed;
        break;
    case Vibration::Right:
        xInputVibration.wRightMotorSpeed = motorSpeed;
        break;
    }
    XInputSetState(_controllerIndex, &xInputVibration);
}

void Input::Device::Controller::StopVibration()
{
    XINPUT_VIBRATION vibration{};
    XInputSetState(_controllerIndex, &vibration);
}

unsigned short Input::Device::Controller::GetFlag(Button button)
{
    int flag = 1;
    for (int i = 0; i < static_cast<int>(button); ++i) flag = flag << 1;
    return static_cast<unsigned short>(flag);
}

bool Input::Device::Controller::CheckConnection()
{
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state{};
        const DWORD result = XInputGetState(i, &state);
        if (result == ERROR_SUCCESS)
        {
            _controllerIndex = i;
            break;
        }
    }
    return _controllerIndex != Disconnection;
}
