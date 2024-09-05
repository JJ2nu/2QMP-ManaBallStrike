#pragma once

namespace Exception
{
    class UnicodeException : public std::exception
    {
    public:
        UnicodeException() = default;
        explicit UnicodeException(std::wstring message);
        explicit UnicodeException(const wchar_t* message);

        [[nodiscard]] std::wstring_view UnicodeWhat() const noexcept;

    private:
        static std::string ConvertToMultibyte(const std::wstring& string);
        std::wstring _message;
    };
}