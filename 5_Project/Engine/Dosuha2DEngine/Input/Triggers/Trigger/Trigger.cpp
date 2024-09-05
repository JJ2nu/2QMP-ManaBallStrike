#include "pch.h"
#include "Trigger.hpp"

Input::Value Input::Trigger::Trigger::GetModifiedValue(const Value value) const
{
    return std::accumulate(_modifiers.begin(), _modifiers.end(), value,
                           [](Value v, const std::unique_ptr<Modifier::IModifier>& modifier)
                           {
                               return modifier->operator()(v);
                           });
}

void Input::Trigger::Trigger::Pull(const TriggerState state, const Value& value) const
{
    _onTriggered(state, value);
}


void Input::Trigger::Trigger::SetComponent(const Component::IComponent* component)
{
    _component = component;
}

void Input::Trigger::Trigger::BindOnTriggered(const std::function<void(TriggerState, const Value&)>& onTriggered)
{
    _onTriggered = onTriggered;
}

Input::Value Input::Trigger::Trigger::GetRawValue() const
{
    return _component->GetValue();
}
