#include "pch.h"
#include "Action_.h"

void Input::Action_::Update(float deltaTime)
{
    std::ranges::for_each(_triggers, [deltaTime](auto& trigger) { trigger->Update(deltaTime); });
    if (_isTriggered) _states.at(_state)->Execute(_value);
}

void Input::Action_::Reset()
{
    _value = Value::Zero();
    _state = TriggerState::Completed;
    _isTriggered = false;
}

const std::unordered_map<Input::TriggerState, std::unique_ptr<Input::Trigger::State>>*
Input::Action_::GetStatesPointer() const
{
    return &_states;
}

void Input::Action_::AddListener(const TriggerState state, Listener&& listener) const
{
    _states.at(state)->AddListener(std::forward<Listener>(listener));
}

void Input::Action_::ClearListener()
{
    std::ranges::for_each(_states, [](const auto& state) { state.second->ClearListener(); });
}

void Input::Action_::OnTriggered(const TriggerState state, const Value& value)
{
    if (_state < state) _state = state;
    _value += value;
    _isTriggered = true;
}

bool Input::Action_::GetTriggered() const
{
    return _isTriggered;
}

Input::Action_::Action_()
    : _isTriggered(false), _state(TriggerState::Completed), _value(Value::Zero())
{
    _states[TriggerState::Triggered] = std::make_unique<Trigger::State>();
    _states[TriggerState::Started] = std::make_unique<Trigger::State>();
    _states[TriggerState::Ongoing] = std::make_unique<Trigger::State>();
    _states[TriggerState::Completed] = std::make_unique<Trigger::State>();
    _states[TriggerState::Canceled] = std::make_unique<Trigger::State>();
}
