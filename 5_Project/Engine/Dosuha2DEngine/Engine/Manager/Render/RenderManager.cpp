#include "pch.h"
#include "RenderManager.h"

void Engine::Manager::Render::Initialize(const Microsoft::WRL::ComPtr<::Render::ISystem>& system)
{
    GetInstance()->_system = system;
    GetInstance()->_system->CreateRenderer(&GetInstance()->_renderer);
    GetInstance()->_system->CreateShader(&GetInstance()->_shader);
}

void Engine::Manager::Render::Finalize()
{
    GetInstance()->_renderer = nullptr;
    GetInstance()->_shader = nullptr;
    GetInstance()->_system = nullptr;
}

void Engine::Manager::Render::BeginDraw()
{
    GetInstance()->_system->BeginDraw();
}

void Engine::Manager::Render::Clear(const D2D1_COLOR_F color)
{
    GetInstance()->_system->Clear(color);
}

void Engine::Manager::Render::EndDraw()
{
    GetInstance()->_system->EndDraw();
}

Microsoft::WRL::ComPtr<::Render::IRenderer> Engine::Manager::Render::GetRenderer()
{
    return GetInstance()->_renderer;
}

Microsoft::WRL::ComPtr<::Render::IShader> Engine::Manager::Render::GetShader()
{
    return GetInstance()->_shader;
}

Engine::Manager::Render::Render()
    : _system(nullptr)
{
}
