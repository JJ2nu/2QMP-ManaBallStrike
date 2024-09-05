#pragma once
#include "../../Component/Button/Button.h"

namespace Input::Device
{
    class Keyboard : public IKeyboard
    {
    public:
        Keyboard();
        
        void Update() override;
        void Reset() override;

        Component::IComponent* GetComponent(Key key) override;

    private:
        std::unordered_map<Key, Component::Button> _keys;
    };
}
