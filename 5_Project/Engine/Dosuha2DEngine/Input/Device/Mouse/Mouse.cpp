#include "pch.h"
#include "Mouse.h"

Input::Device::Mouse::Mouse()
    : _handle(nullptr), _axes(static_cast<size_t>(Axis::Max)), _buttons(static_cast<size_t>(Button::Max))
{
}

void Input::Device::Mouse::SetHandle(const HWND handle)
{
    _handle = handle;
}

void Input::Device::Mouse::Update()
{
    UpdateAxis();
    UpdateButton();
}

void Input::Device::Mouse::Reset()
{
    std::ranges::for_each(_axes, [](auto& axis) { axis.second.Reset(); });
    std::ranges::for_each(_buttons, [](auto& button) { button.second.Reset(); });
}

Input::Component::IComponent* Input::Device::Mouse::GetComponent(const Button button)
{
    return &_buttons[button];
}

Input::Component::IComponent* Input::Device::Mouse::GetComponent(const Axis axis)
{
    return &_axes[axis];
}

Input::Value Input::Device::Mouse::GetPosition() const
{
    Value value{};
    value.x = _axes.at(Axis::X).GetValue().scalar;
    value.y = _axes.at(Axis::Y).GetValue().scalar;
    return value;
}

void Input::Device::Mouse::UpdateAxis()
{
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    ScreenToClient(_handle, &mousePosition);

    _axes[Axis::X].SetValue(mousePosition.x);
    _axes[Axis::Y].SetValue(mousePosition.y);

    MSG message;
    if (PeekMessage(&message, _handle, NULL, NULL, PM_NOREMOVE)
        && message.message == WM_MOUSEWHEEL)
        _axes[Axis::Wheel].SetValue(GET_WHEEL_DELTA_WPARAM(message.wParam));
}

void Input::Device::Mouse::UpdateButton()
{
    for (unsigned char buttonIndex = 0; buttonIndex < static_cast<unsigned char>(Button::Max); ++buttonIndex)
    {
        _buttons[static_cast<Button>(buttonIndex)].SetValue(GetAsyncKeyState(buttonIndex) & 0x8000);
    }
}
