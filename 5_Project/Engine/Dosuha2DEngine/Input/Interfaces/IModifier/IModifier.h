#pragma once

namespace Input::Modifier
{
    struct IModifier
    {
        IModifier() = default;
        IModifier(const IModifier& other) = default;
        IModifier(IModifier&& other) noexcept = default;
        IModifier& operator=(const IModifier& other) = default;
        IModifier& operator=(IModifier&& other) noexcept = default;
        virtual ~IModifier() = default;

        virtual Value& operator()(Value& value) const = 0;

        int a;
    };
}
