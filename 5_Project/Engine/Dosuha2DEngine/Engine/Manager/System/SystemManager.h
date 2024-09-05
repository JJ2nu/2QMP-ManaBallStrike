#pragma once

namespace Engine::Manager
{
    class System : public Base<System>
    {
        friend const std::shared_ptr<System>& Manager::Base<System>::GetInstance();

    public:
        static void Initialize(HWND windowHandle, Math::Vector2 size);
        static void Finalize();

        static Microsoft::WRL::ComPtr<::Render::ISystem> GetRenderSystem();
        static Dosuha::Pointer<::Animation::ISystem> GetAnimationSystem();
        
    protected:
        System();

    private:
        Microsoft::WRL::ComPtr<::Render::ISystem> _renderSystem;
        Dosuha::Pointer<::Animation::ISystem> _animationSystem;
    };
}
