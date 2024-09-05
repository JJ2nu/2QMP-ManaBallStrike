#pragma once

namespace Input::Device
{
    template <typename T>
    struct IComponentContainer
    {
        IComponentContainer() = default;
        IComponentContainer(const IComponentContainer&) = default;
        IComponentContainer& operator=(const IComponentContainer&) = default;
        IComponentContainer(IComponentContainer&&) = default;
        IComponentContainer& operator=(IComponentContainer&&) = default;
        virtual ~IComponentContainer() = default;

        virtual Component::IComponent* GetComponent(T id) = 0;
    };
}
