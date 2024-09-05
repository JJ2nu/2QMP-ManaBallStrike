#include "pch.h"
#include "InputManager.h"

void Engine::Manager::Input::Initialize()
{
    GetInstance()->_system = std::unique_ptr<::Input::ISystem>(::Input::CreateSystem());
}

void Engine::Manager::Input::Update(const float deltaTime)
{
    GetInstance()->_system->Update(deltaTime);
}

void Engine::Manager::Input::Reset()
{
    GetInstance()->_system->Reset();
}

Input::Device::IKeyboard& Engine::Manager::Input::GetKeyboard()
{
    return GetInstance()->_system->GetKeyboard();
}

Input::Device::IMouse& Engine::Manager::Input::GetMouse()
{
    return GetInstance()->_system->GetMouse();
}

Input::Device::IController& Engine::Manager::Input::GetController()
{
    return GetInstance()->_system->GetController();
}

std::shared_ptr<Input::IMappingContext> Engine::Manager::Input::CreateMappingContext(const std::wstring& name)
{
    if (!GetInstance()->_mappingContexts.contains(name))
        GetInstance()->_mappingContexts[name] = std::shared_ptr<::Input::IMappingContext>(GetInstance()->_system->CreateMappingContext());
    return GetInstance()->_mappingContexts[name];
}

void Engine::Manager::Input::SetMappingContext(const std::shared_ptr<::Input::IMappingContext>& mappingContext)
{
    GetInstance()->_system->SetMappingContext(mappingContext.get());
}

Engine::Manager::Input::Input()
    : _system(nullptr)
{
}
