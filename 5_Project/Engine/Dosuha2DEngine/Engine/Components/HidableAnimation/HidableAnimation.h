#pragma once

namespace Engine::Component
{
    class HidableAnimation : public Animation
    {
    public:
        HidableAnimation(const std::wstring& bitmapPath, const std::wstring& animationPath);
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;

        void Show();
        void Hide();

    private:
        bool _isShown;
    };
}
