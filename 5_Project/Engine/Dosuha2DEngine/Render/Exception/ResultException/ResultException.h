#pragma once

namespace Render::Exception
{
    class ResultException : public ::Exception::UnicodeException
    {
    public:
        ResultException() = default;
        ResultException(HRESULT result, std::wstring message);
        ResultException(HRESULT result, const wchar_t* message);

        [[nodiscard]] HRESULT GetResult() const noexcept;

    private:
        HRESULT _result;
    };
}
