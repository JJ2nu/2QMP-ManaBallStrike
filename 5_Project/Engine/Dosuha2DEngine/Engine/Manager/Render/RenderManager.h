#pragma once

namespace Engine::Manager
{
    class Render : public Base<Render>
    {
        friend const std::shared_ptr<Render>& Manager::Base<Render>::GetInstance();

    public:
        using Renderer = Microsoft::WRL::ComPtr<::Render::IRenderer>;
        using Shader = Microsoft::WRL::ComPtr<::Render::IShader>;

        static void Initialize(const Microsoft::WRL::ComPtr<::Render::ISystem>& system);
        static void Finalize();

        static void BeginDraw();
        static void Clear(D2D1_COLOR_F color);
        static void EndDraw();

        static Microsoft::WRL::ComPtr<::Render::IRenderer> GetRenderer();
        static Microsoft::WRL::ComPtr<::Render::IShader> GetShader();

    protected:
        Render();

    private:
        Microsoft::WRL::ComPtr<::Render::IRenderer> _renderer;
        Microsoft::WRL::ComPtr<::Render::IShader> _shader;
        Microsoft::WRL::ComPtr<::Render::ISystem> _system;
    };
}
