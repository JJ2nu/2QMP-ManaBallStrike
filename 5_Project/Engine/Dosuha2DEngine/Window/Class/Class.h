#pragma once

namespace Window
{
    class Class : public IClass
    {
    public:
        Class(HINSTANCE instanceHandle, LPCWSTR name, HCURSOR cursor, HICON icon, HICON smIcon);
        [[nodiscard]] LPCWSTR GetName() const override;

        static HCURSOR GetCursor(const WCHAR* path);
        static HICON GetIcon(const WCHAR* path);
        static HICON GetSmallIcon(const WCHAR* path);
        
        void AddReference() override;
        long Release() override;

    private:
        static LRESULT DefaultWindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
        static void PlaceInCenterOfScreen(HWND windowHandle);

        WNDCLASSEX _windowClass;
        std::atomic<long> _referenceCount;
    };
}
