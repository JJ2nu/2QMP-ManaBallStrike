#pragma once
#include "../../Triggers/ChordAction/ChordAction.h"
#include "../../Action/Action_.h"

namespace Input
{
    struct IModifier;

    template <typename T>
    concept IsModifier = std::derived_from<T, Modifier::IModifier>;

    class Action
    {
        friend class MappingContext;

    public:
        template <typename Trigger, typename... Modifiers>
            requires std::derived_from<Trigger, Input::Trigger::Trigger> && (IsModifier<Modifiers> && ...)
        decltype(auto) BindKey(Component::IComponent* component)
        {
            Trigger* trigger;
            auto iTrigger = _action->CreateTrigger<Trigger>(&trigger);
            (trigger->template SetModifier<Modifiers>(), ...);
            trigger->SetComponent(component);
            return iTrigger;
        }
        
        template <typename Trigger, typename... Modifiers>
            requires std::derived_from<Trigger, Input::Trigger::IChordAction> && (IsModifier<Modifiers> && ...)
        decltype(auto) BindKey(const std::shared_ptr<Action>& action, Component::IComponent* component)
        {
            Trigger* trigger;
            auto iTrigger = _action->CreateTrigger<Trigger>(&trigger, action->_action);
            (trigger->template SetModifier<Modifiers>(), ...);
            trigger->SetComponent(component);
            return iTrigger;
        }

        void AddListener(TriggerState state, Listener listener) const;
        void ClearListener() const;

    private:
        explicit Action(const std::shared_ptr<Action_>& action);

        std::shared_ptr<Action_> _action;
    };
}
