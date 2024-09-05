#include "pch.h"
#include "UnicodeException.h"

Exception::UnicodeException::UnicodeException(std::wstring message)
    : std::exception(ConvertToMultibyte(message).c_str()), _message(std::move(message))
{
}

Exception::UnicodeException::UnicodeException(const wchar_t* message)
    : UnicodeException(std::wstring(message))
{
}

std::wstring_view Exception::UnicodeException::UnicodeWhat() const noexcept
{
    return _message;
}

std::string Exception::UnicodeException::ConvertToMultibyte(const std::wstring& string)
{
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(string);
}
