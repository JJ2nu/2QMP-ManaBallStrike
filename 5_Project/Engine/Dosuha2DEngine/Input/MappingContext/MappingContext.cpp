#include "pch.h"
#include "MappingContext.h"

#include <memory>

#include "../Action/Action_.h"

void Input::MappingContext::Update(const float deltaTime)
{
    std::ranges::for_each(_actions, [deltaTime](auto& action) { action.second->Update(deltaTime); });
}

void Input::MappingContext::Reset()
{
    std::ranges::for_each(_actions, [](auto& action) { action.second->Reset(); });
}

std::shared_ptr<Input::Action> Input::MappingContext::CreateAction(const std::wstring_view& name)
{
    if (_actions.contains(name)) ThrowRuntimeErrorIf<Exception::RuntimeException>()(true, L"Action already exists.");
    _actions[name] = std::make_shared<Action_>();
    return std::shared_ptr<Action>(new Action(_actions[name]));
}

std::shared_ptr<Input::Action> Input::MappingContext::GetAction(const std::wstring_view& name)
{
    if (!_actions.contains(name)) ThrowRuntimeErrorIf<Exception::RuntimeException>()(true, L"Action does not exist.");
    return std::shared_ptr<Action>(new Action(_actions[name]));
}
