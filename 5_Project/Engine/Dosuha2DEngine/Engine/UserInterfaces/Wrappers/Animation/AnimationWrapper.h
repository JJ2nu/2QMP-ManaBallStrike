#pragma once

namespace Engine::UI::Wrapper
{
    class Animation : public Image
    {
    public:
        Animation(const Math::Vector2& size, std::wstring bitmapPath, std::wstring animationPath);

        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;
        void Finalize() override;

        void SetMotion(const std::wstring& name) const;

        void BindMotionBeginEvent(const std::wstring& name, const std::function<void()>& event) const;
        void BindMotionEndEvent(const std::wstring& name, const std::function<void()>& event) const;
        void BindFrameEvent(const std::wstring& motionName, size_t frameIndex, const std::function<void()>& event) const;
        void BindLastFrameEvent(const std::wstring& motionName, const std::function<void()>& event) const;

    private:
        std::wstring _animationPath;
        Dosuha::Pointer<::Animation::IAsset> _animationAsset;
    };
}
