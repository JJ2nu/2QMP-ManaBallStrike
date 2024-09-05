#pragma once

namespace Engine::UI::Wrapper
{
    class Image : public Base
    {
    public:
        Image(std::wstring path);
        Image(const Math::Vector2& size, std::wstring path);

        void Initialize(Manager::Resource::Loader loader) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;
        void Finalize() override;

    protected:
        Microsoft::WRL::ComPtr<ID2D1Bitmap> _bitmap;

    private:
        std::wstring _path;
    };
}
