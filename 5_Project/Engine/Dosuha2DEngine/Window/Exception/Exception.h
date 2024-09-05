#pragma once

#include "WinAPIException/WinAPIException.h"

template <typename T> requires std::is_base_of_v<Window::Exception::WinAPIException, T>
struct ThrowLastErrorIf
{
    void operator()(const bool expression, const std::wstring& message) const
    {
        if (expression) throw T(GetLastError(), message);
    }
};
