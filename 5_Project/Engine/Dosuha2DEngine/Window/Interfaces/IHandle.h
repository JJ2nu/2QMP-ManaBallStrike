#pragma once

namespace Window
{
    struct IHandle : Dosuha::IReferenceCounter
    {
        virtual void Show(int showCommand = SW_NORMAL) const = 0;
        virtual void Update() const = 0;
        virtual HWND Get() const = 0;
    };
}
