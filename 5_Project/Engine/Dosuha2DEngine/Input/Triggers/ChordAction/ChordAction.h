#pragma once
#include "../Trigger/Trigger.hpp"

namespace Input
{
    class Action_;
}

namespace Input::Trigger
{
    class ChordAction : public Trigger, public IChordAction
    {
    public:
        explicit ChordAction(const std::shared_ptr<Action_>& action);
        
        void Update(float deltaTime) override;

    private:
        std::shared_ptr<Action_> _action;
        bool _isDown;
    };
}
