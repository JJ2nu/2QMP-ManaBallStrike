#include "pch.h"
#include "Action.hpp"

Input::Action::Action(const std::shared_ptr<Action_>& action)
    : _action(action)
{
}


void Input::Action::AddListener(const TriggerState state, Listener listener) const
{
    _action->AddListener(state, std::move(listener));
}

void Input::Action::ClearListener() const
{
    _action->ClearListener();
}
