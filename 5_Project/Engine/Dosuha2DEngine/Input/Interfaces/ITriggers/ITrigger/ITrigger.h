#pragma once

namespace Input::Trigger
{
    struct ITrigger
    {
        ITrigger() = default;
        ITrigger(const ITrigger& other) = default;
        ITrigger(ITrigger&& other) noexcept = default;
        ITrigger& operator=(const ITrigger& other) = default;
        ITrigger& operator=(ITrigger&& other) noexcept = default;
        virtual ~ITrigger() = default;

        virtual void Update(float deltaTime) = 0;
        virtual void BindOnTriggered(const std::function<void(TriggerState, const Value&)>& onTriggered) = 0;
    };
}
