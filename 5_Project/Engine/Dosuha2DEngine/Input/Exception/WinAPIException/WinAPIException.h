#pragma once

namespace Input::Exception
{
    class WinAPIException : public ::Exception::UnicodeException
    {
    public:
        WinAPIException() = default;
        WinAPIException(DWORD errorCode, std::wstring message);
        WinAPIException(DWORD errorCode, const wchar_t* message);

        [[nodiscard]] DWORD GetErrorCode() const noexcept;

    private:
        static std::wstring FormatErrorMessage(DWORD errorCode, const std::wstring& message);
        DWORD _errorCode;
    };
}
