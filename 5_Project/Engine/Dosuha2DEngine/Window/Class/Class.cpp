#include "pch.h"
#include "Class.h"

Window::Class::Class(const HINSTANCE instanceHandle, const LPCWSTR name, const HCURSOR cursor, const HICON icon, const HICON smIcon)
    : _windowClass({
          sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, DefaultWindowProcedure,
          NULL, NULL, instanceHandle, icon, cursor, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
          nullptr, name, smIcon
      }),
      _referenceCount(1)
{
    ThrowLastErrorIf<Exception::WinAPIException>()
        (RegisterClassEx(&_windowClass) == FALSE, L"Register window class fail.");
}

LPCWSTR Window::Class::GetName() const
{
    return _windowClass.lpszClassName;
}

HCURSOR Window::Class::GetCursor(const WCHAR* path)
{
    const HCURSOR cursor = static_cast<HCURSOR>(LoadImage(nullptr, path, IMAGE_CURSOR, 32, 32, LR_LOADFROMFILE));
    ICONINFO info;
    GetIconInfo(cursor, &info);
    info.xHotspot = 0;
    info.yHotspot = 0;
    return CreateIconIndirect(&info);
}

HICON Window::Class::GetIcon(const WCHAR* path)
{
    return static_cast<HICON>(LoadImage(nullptr, path, IMAGE_ICON, 256, 256, LR_LOADFROMFILE));
}

HICON Window::Class::GetSmallIcon(const WCHAR* path)
{
    return static_cast<HICON>(LoadImage(nullptr, path, IMAGE_ICON, 64, 64, LR_LOADFROMFILE));
}

void Window::Class::AddReference()
{
    ++_referenceCount;
}

long Window::Class::Release()
{
    if (--_referenceCount > 0) return _referenceCount;
    delete this;
    return 0;
}

LRESULT Window::Class::DefaultWindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam,
                                              const LPARAM lParam)
{
    RECT rect;

    switch (message)
    {
    case WM_CREATE:
        PlaceInCenterOfScreen(windowHandle);
        break;
    case WM_DESTROY:
        ClipCursor(nullptr);
        PostQuitMessage(0);
        break;
    case WM_ACTIVATE:
        if (LOWORD(message) != WA_INACTIVE)
        {
            GetWindowRect(windowHandle, &rect); // hWnd는 게임 창의 핸들
            rect.left += 10;
            rect.top += 35;
            rect.right -= 10;
            rect.bottom -= 10;
            ClipCursor(&rect);
        }
        break;
    default:
        return DefWindowProc(windowHandle, message, wParam, lParam);
    }
    return 0;
}

void Window::Class::PlaceInCenterOfScreen(const HWND windowHandle)
{
    const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    RECT rect;
    GetClientRect(windowHandle, &rect);
    ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    const int clientWidth = rect.right - rect.left;
    const int clientHeight = rect.bottom - rect.top;
    SetWindowPos(windowHandle, nullptr, screenWidth / 2 - clientWidth / 2, screenHeight / 2 - clientHeight / 2,
                 clientWidth, clientHeight, NULL);
}
