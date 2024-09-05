#include "pch.h"
#include "RuntimeException.h"

Input::Exception::RuntimeException::RuntimeException(std::wstring message)
    : UnicodeException(std::move(message))
{
}

Input::Exception::RuntimeException::RuntimeException(const wchar_t* message)
    : UnicodeException(message)
{
}
