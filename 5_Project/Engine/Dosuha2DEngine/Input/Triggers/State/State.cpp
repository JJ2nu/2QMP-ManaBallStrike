#include "pch.h"
#include "State.h"

void Input::Trigger::State::AddListener(Listener&& listener)
{
    _listeners.push_back(std::forward<Listener>(listener));
}

void Input::Trigger::State::ClearListener()
{
    _listeners.clear();
}

void Input::Trigger::State::Execute(const Value& value)
{
    std::ranges::for_each(_listeners, [&](const Listener& listener) { listener(value); });
}
