#pragma once

#include "RuntimeException/RuntimeException.h"
#include "WinAPIException/WinAPIException.h"

template <typename T> requires std::is_base_of_v<Input::Exception::WinAPIException, T>
struct ThrowLastErrorIf
{
    void operator()(const bool expression, const std::wstring& message) const
    {
        if (expression) throw T(GetLastError(), message);
    }
};

template <typename T> requires std::is_base_of_v<Input::Exception::RuntimeException, T>
struct ThrowRuntimeErrorIf
{
    void operator()(const bool expression, const std::wstring& message) const
    {
        if (expression) throw T(message);
    }
};
