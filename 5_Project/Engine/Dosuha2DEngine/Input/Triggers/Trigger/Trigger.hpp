#pragma once

namespace Input::Trigger
{
    class Trigger : public ITrigger
    {
    public:
        Trigger() = default;
        
        template <typename T> requires std::derived_from<T, Modifier::IModifier>
        void SetModifier()
        {
            _modifiers.emplace_back(new T());
        }

        void SetComponent(const Component::IComponent* component);
        void BindOnTriggered(const std::function<void(TriggerState, const Value&)>& onTriggered) override;

    protected:
        [[nodiscard]] Value GetRawValue() const;
        [[nodiscard]] Value GetModifiedValue(Value value) const;
        void Pull(TriggerState state, const Value& value) const;

    private:
        std::vector<std::unique_ptr<Modifier::IModifier>> _modifiers;
        const Component::IComponent* _component;
        std::function<void(TriggerState, const Value&)> _onTriggered;
    };
}
