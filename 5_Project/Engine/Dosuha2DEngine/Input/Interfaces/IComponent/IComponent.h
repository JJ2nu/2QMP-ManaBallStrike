#pragma once

namespace Input::Component
{
    struct IComponent
    {
        IComponent() = default;
        IComponent(const IComponent&) = default;
        IComponent& operator=(const IComponent&) = default;
        IComponent(IComponent&&) = default;
        IComponent& operator=(IComponent&&) = default;
        virtual ~IComponent() = default;

        [[nodiscard]] virtual Value GetValue() const = 0;
        virtual void Reset() = 0;
    };
}