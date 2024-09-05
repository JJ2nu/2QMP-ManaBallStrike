#pragma once
#include "Triggers/State/State.h"
#include "Triggers/Triggers.h"

namespace Input
{
    class Action_
    {
    public:
        Action_();

        void Update(float deltaTime);
        void Reset();
        const std::unordered_map<TriggerState, std::unique_ptr<Trigger::State>>* GetStatesPointer() const;
        void AddListener(TriggerState state, Listener&& listener) const;
        void ClearListener();

        template <typename ChordAction> requires std::derived_from<ChordAction, Trigger::IChordAction>
        Trigger::IChordAction* CreateTrigger(ChordAction** chordAction, std::shared_ptr<Action_> action) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::ChordAction>(action)));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *chordAction = static_cast<ChordAction*>(_triggers.back().get());
            return *chordAction;
        }

        template <typename Down> requires std::derived_from<Down, Trigger::IDown>
        Trigger::IDown* CreateTrigger(Down** down) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::Down>()));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *down = static_cast<Down*>(_triggers.back().get());
            return *down;
        }

        template <typename Hold> requires std::derived_from<Hold, Trigger::IHold>
        Trigger::IHold* CreateTrigger(Hold** hold) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::Hold>()));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *hold = static_cast<Hold*>(_triggers.back().get());
            return *hold;
        }

        template <typename HoldAndRelease> requires std::derived_from<HoldAndRelease, Trigger::IHoldAndRelease>
        Trigger::IHoldAndRelease* CreateTrigger(HoldAndRelease** holdAndRelease) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::HoldAndRelease>()));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *holdAndRelease = static_cast<HoldAndRelease*>(_triggers.back().get());
            return *holdAndRelease;
        }

        template <typename Pressed> requires std::derived_from<Pressed, Trigger::IPressed>
        Trigger::IPressed* CreateTrigger(Pressed** pressed) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::Pressed>()));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *pressed = static_cast<Pressed*>(_triggers.back().get());
            return *pressed;
        }

        template <typename Pulse> requires std::derived_from<Pulse, Trigger::IPulse>
        Trigger::IPulse* CreateTrigger(Pulse** pulse) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::Pulse>()));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *pulse = static_cast<Pulse*>(_triggers.back().get());
            return *pulse;
        }

        template <typename Released> requires std::is_same_v<Released, Trigger::IReleased>
        Trigger::IReleased* CreateTrigger(Released** released) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::Released>()));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *released = static_cast<Released*>(_triggers.back().get());
            return *released;
        }

        template <typename Tap> requires std::derived_from<Tap, Trigger::ITap>
        Trigger::ITap* CreateTrigger(Tap** tap) 
        {
            _triggers.push_back(std::move(std::make_unique<Trigger::Tap>()));
            _triggers.back()->BindOnTriggered(std::bind(&Action_::OnTriggered, this, std::placeholders::_1, std::placeholders::_2));
            *tap = static_cast<Tap*>(_triggers.back().get());
            return *tap;
        }

        void OnTriggered(TriggerState state, const Value& value);

        [[nodiscard]] bool GetTriggered() const;

    private:
        std::unordered_map<TriggerState, std::unique_ptr<Trigger::State>> _states;
        std::vector<std::unique_ptr<Trigger::ITrigger>> _triggers;

        bool _isTriggered;
        TriggerState _state;
        Value _value;
    };
}
