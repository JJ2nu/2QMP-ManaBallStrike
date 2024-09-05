#pragma once

namespace Window
{
    struct IClass : Dosuha::IReferenceCounter
    {
        [[nodiscard]] virtual LPCWSTR GetName() const = 0;
    };
}
