#include "pch.h"
#include "Button.h"

Input::Component::Button::Button()
    : _value(false)
{
}

void Input::Component::Button::SetValue(const bool value)
{
    _value = value;
}

void Input::Component::Button::Reset()
{
    _value = false;
}

Input::Value Input::Component::Button::GetValue() const
{
    Value value{};
    value.scalar = _value ? 1.0f : 0.0f;
    return value;
}
