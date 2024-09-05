#include "pch.h"
#include "Handle.h"

Window::Handle::Handle(const HINSTANCE instanceHandle, const LPCWSTR className, const RECT windowRect)
    : _referenceCount(1)
{
    _windowHandle = CreateWindow(className, className, WS_OVERLAPPEDWINDOW,
                                 windowRect.left, windowRect.top, windowRect.right - windowRect.left,
                                 windowRect.bottom - windowRect.top, nullptr, nullptr,
                                 instanceHandle, nullptr);
    ThrowLastErrorIf<Exception::WinAPIException>()
        (_windowHandle == nullptr, L"Create window fail.");
}

Window::Handle::~Handle()
{
    if (_windowHandle != nullptr) DestroyWindow(_windowHandle);
    _windowHandle = nullptr;
}

void Window::Handle::Show(const int showCommand) const
{
    ShowWindow(_windowHandle, showCommand);
}

void Window::Handle::Update() const
{
    ThrowLastErrorIf<Exception::WinAPIException>()
        (UpdateWindow(_windowHandle) == FALSE, L"Update window fail.");
}

void Window::Handle::AddReference()
{
    ++_referenceCount;
}

long Window::Handle::Release()
{
    if (--_referenceCount > 0) return _referenceCount;
    delete this;
    return 0;
}

HWND Window::Handle::Get() const
{
    return _windowHandle;
}
