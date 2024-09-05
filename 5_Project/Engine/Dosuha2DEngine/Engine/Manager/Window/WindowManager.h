#pragma once
#include "../Base/ManagerBase.hpp"


namespace Engine::Manager
{
    class Window : public Base<Window>
    {
        friend const std::shared_ptr<Window>& Manager::Base<Window>::GetInstance();

    public:
        static void Initialize(HINSTANCE instanceHandle, LPCWSTR gameName, Math::Vector2 size, int showCommand);

        static HWND GetWindowHandle();

        static Math::Vector2 GetSize();

    protected:
        Window();

    private:
        Dosuha::Pointer<::Window::ISystem> _system;
        Dosuha::Pointer<::Window::IHandle> _handle;
        Dosuha::Pointer<::Window::IClass> _class;

        Math::Vector2 _size;
    };
}
