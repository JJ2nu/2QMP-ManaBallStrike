#pragma once

namespace Engine::Component
{
    class Animation : public Bitmap
    {
        struct AnimationInfo;
        struct FrameInfo;

    public:
        Animation(const std::wstring& bitmapPath, const std::wstring& animationPath);
        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
        void Finalize() override;
        void SetMirror(bool isMirror = false);
        void SetMotion(const std::wstring& name);

    protected:
        void UpdateCenterTransform() override;
        void UpdateMirrorMatrix();
        Dosuha::Pointer<::Animation::IAsset> _animationAsset;

    private:
        std::wstring _animationPath;
        bool _isMirror;
        D2D1::Matrix3x2F _mirrorMatrix;
    };
}
