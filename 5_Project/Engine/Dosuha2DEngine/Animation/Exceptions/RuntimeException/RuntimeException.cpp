#include "pch.h"
#include "RuntimeException.h"

Animation::Exception::RuntimeException::RuntimeException(std::wstring message)
    : UnicodeException(std::move(message))
{
}

Animation::Exception::RuntimeException::RuntimeException(const wchar_t* message)
    : UnicodeException(message)
{
}
