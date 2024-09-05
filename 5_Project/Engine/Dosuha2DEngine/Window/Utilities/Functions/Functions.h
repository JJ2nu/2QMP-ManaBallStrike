#pragma once

namespace Window
{
    void CreateSystem(HINSTANCE instanceHandle, ISystem** system);
    RECT AdjustWindowRect(SIZE size);
}
