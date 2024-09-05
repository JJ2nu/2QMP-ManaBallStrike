#include "pch.h"
#include "ChordAction.h"

Input::Trigger::ChordAction::ChordAction(const std::shared_ptr<Action_>& action)
    : _action(action), _isDown(false)
{
}

void Input::Trigger::ChordAction::Update(float deltaTime)
{
    if (!_action->GetTriggered())
    {
        _isDown = false;
    }
    else
    {
        const Value value = GetModifiedValue(GetRawValue());
        const bool isDown = value != Value::Zero();
        if (isDown && !_isDown) Pull(TriggerState::Started, value);
        else if (isDown && _isDown) Pull(TriggerState::Triggered, value);
        else if (!isDown && _isDown) Pull(TriggerState::Completed, value);
        _isDown = isDown;
    }
}
