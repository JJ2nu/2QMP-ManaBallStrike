#include "pch.h"
#include "Down.h"

void Input::Trigger::Down::Update(float deltaTime)
{
    const Value value = GetModifiedValue(GetRawValue());
    const bool isDown = value != Value::Zero();
    if (isDown && !_isDown) Pull(TriggerState::Started, value);
    else if (isDown && _isDown) Pull(TriggerState::Triggered, value);
    else if (!isDown && _isDown) Pull(TriggerState::Completed, value);
    _isDown = isDown;
}
