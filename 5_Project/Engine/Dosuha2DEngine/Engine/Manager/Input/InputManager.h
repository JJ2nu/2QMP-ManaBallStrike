#pragma once

namespace Engine::Manager
{
    class Input : public Base<Input>
    {
        friend const std::shared_ptr<Input>& Manager::Base<Input>::GetInstance();

    public:
        static void Initialize();
        static void Update(float deltaTime);
        static void Reset();

        static ::Input::Device::IKeyboard& GetKeyboard();
        static ::Input::Device::IMouse& GetMouse();
        static ::Input::Device::IController& GetController();

        static std::shared_ptr<::Input::IMappingContext> CreateMappingContext(const std::wstring& name);
        static void SetMappingContext(const std::shared_ptr<::Input::IMappingContext>& mappingContext);

    protected:
        Input();

    private:
        std::unique_ptr<::Input::ISystem> _system;

        std::unordered_map<std::wstring, std::shared_ptr<::Input::IMappingContext>> _mappingContexts;
    };
}
