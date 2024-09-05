#pragma once

namespace Input::Exception
{
    class RuntimeException : public ::Exception::UnicodeException
    {
    public:
        RuntimeException() = default;
        RuntimeException(std::wstring message);
        RuntimeException(const wchar_t* message);
    };
}
