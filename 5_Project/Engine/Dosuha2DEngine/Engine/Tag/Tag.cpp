#include "pch.h"
#include "Tag.h"

Engine::Tag::Tag(const std::wstring_view name)
    : _name(name), _value(std::nullopt)
{
}

Engine::Tag::Tag(const std::wstring_view name, const float value)
    : _name(name), _value(value)
{
}

std::wstring_view Engine::Tag::GetName() const
{
    return _name;
}

std::optional<float> Engine::Tag::GetValue() const
{
    return _value;
}

std::strong_ordering Engine::Tag::operator<=>(const Tag& lhs) const
{
    return _name <=> lhs._name;
}

bool Engine::Tag::operator==(const Tag& lhs) const
{
    return _name == lhs._name;
}

