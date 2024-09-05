#pragma once

namespace Engine::Component
{
    class Bitmap : public Base, public Scene
    {
    public:
        explicit Bitmap(std::wstring path);

        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
        void Finalize() override;

        Math::Vector2 GetSize() const;

    protected:
        void UpdateCenterTransform() override;

        Microsoft::WRL::ComPtr<ID2D1Bitmap> _bitmap;

    private:
        std::wstring _bitmapPath;
    };
}
