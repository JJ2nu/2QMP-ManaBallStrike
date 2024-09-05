#pragma once

namespace Input::Device
{
    struct IDevice
    {
        IDevice() = default;
        IDevice(const IDevice&) = default;
        IDevice& operator=(const IDevice&) = default;
        IDevice(IDevice&&) = default;
        IDevice& operator=(IDevice&&) = default;
        virtual ~IDevice() = default;

        virtual void Update() = 0;
        virtual void Reset() = 0;
    };
}
