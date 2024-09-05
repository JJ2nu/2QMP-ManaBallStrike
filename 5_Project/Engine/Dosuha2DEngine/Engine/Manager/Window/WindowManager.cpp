#include "pch.h"
#include "WindowManager.h"

void Engine::Manager::Window::Initialize(const HINSTANCE instanceHandle, const LPCWSTR gameName, const Math::Vector2 size, const int showCommand)
{
    CreateSystem(instanceHandle, &GetInstance()->_system);
    GetInstance()->_system->Register(gameName, &GetInstance()->_class, L"Resources/icon_001.cur", L"Resources/manaball_icon.ico", L"Resources/manaball_icon.ico");
    GetInstance()->_system->Create(GetInstance()->_class.Get(), ::Window::AdjustWindowRect(size), &GetInstance()->_handle);
    GetInstance()->_handle->Show(showCommand);
    GetInstance()->_handle->Update();
    GetInstance()->_size = size;
}

HWND Engine::Manager::Window::GetWindowHandle()
{
    return GetInstance()->_handle->Get();
}

Engine::Math::Vector2 Engine::Manager::Window::GetSize()
{
    return GetInstance()->_size;
}

Engine::Manager::Window::Window()
    : _system(nullptr), _handle(nullptr), _class(nullptr), _size(Math::Vector2::Zero())
{
}
