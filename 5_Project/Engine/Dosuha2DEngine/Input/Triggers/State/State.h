#pragma once

namespace Input::Trigger
{
    class State
    {
    public:
        void AddListener(Listener&& listener);
        void ClearListener();
        void Execute(const Value& value);

    private:
        std::vector<Listener> _listeners;
    };
}
