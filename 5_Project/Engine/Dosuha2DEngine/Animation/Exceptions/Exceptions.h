#pragma once

#include "RuntimeException/RuntimeException.h"

template <typename T> requires std::is_base_of_v<Animation::Exception::RuntimeException, T>
struct ThrowRuntimeErrorIf
{
    void operator()(const bool expression, const std::wstring& message) const
    {
        if (expression) throw T(message);
    }
};
