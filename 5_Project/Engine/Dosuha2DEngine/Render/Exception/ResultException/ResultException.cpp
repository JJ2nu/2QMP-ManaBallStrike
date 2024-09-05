#include "pch.h"
#include "ResultException.h"

Render::Exception::ResultException::ResultException(const HRESULT result, std::wstring message)
    :UnicodeException(std::move(message)), _result(result)
{
}

Render::Exception::ResultException::ResultException(const HRESULT result, const wchar_t* message)
    : UnicodeException(message), _result(result)
{
}

HRESULT Render::Exception::ResultException::GetResult() const noexcept
{
    return _result;
}
