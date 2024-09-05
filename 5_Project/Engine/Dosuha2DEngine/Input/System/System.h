#pragma once
#include "../Device/Keyboard/Keyboard.h"
#include "../Device/Mouse/Mouse.h"
#include "../Device/Controller/Controller.h"

namespace Input
{
    class System : public ISystem
    {
    public:
        System();

        void Update(float deltaTime) override;
        void Reset() override;

        void SetMappingContext(IMappingContext* mappingContext) override;
        IMappingContext* CreateMappingContext() override;

        Device::IKeyboard& GetKeyboard() override;
        Device::IMouse& GetMouse() override;
        Device::IController& GetController() override;

    private:
        IMappingContext* _mappingContext;

        Device::Keyboard _keyboard;
        Device::Mouse _mouse;
        Device::Controller _controller;
    };
}
