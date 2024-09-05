#pragma once

namespace Engine::Component
{
    class AlphaBitmap : public Bitmap
    {
    public:
        explicit AlphaBitmap(std::wstring path);

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;

        void SetOpacity(float opacity);
        [[nodiscard]] float GetOpacity() const;

    protected:
        float _opacity;
    };
}
