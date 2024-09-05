#include "pch.h"
#include "Axis.h"

Input::Component::Axis::Axis()
    : _value(0), _sensitivity(1), _deadZone(0)
{
}

Input::Value Input::Component::Axis::GetValue() const
{
    float scalar = static_cast<float>(_value) / static_cast<float>(_sensitivity);
    if (std::abs(scalar) < _deadZone) scalar = 0;
    Value value{};
    value.scalar = scalar;
    return value;
}

long Input::Component::Axis::GetValueRaw() const
{
    return _value;
}

void Input::Component::Axis::Reset()
{
    _value = 0;
}

void Input::Component::Axis::SetDeadZone(const float deadZone)
{
    _deadZone = std::clamp(deadZone, 0.f, 1.f);
}

void Input::Component::Axis::SetSensitivity(const long sensitivity)
{
    _sensitivity = sensitivity;
}

void Input::Component::Axis::SetValue(const long value)
{
    _value = value;
}
