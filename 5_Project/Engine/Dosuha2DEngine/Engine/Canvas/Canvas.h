#pragma once

namespace Engine
{
    class Canvas
    {
    public:
        Canvas(const Math::Vector2& viewportSize);
        Canvas(const Canvas& other) = default;
        Canvas(Canvas&& other) noexcept = default;
        Canvas& operator=(const Canvas& other) = default;
        Canvas& operator=(Canvas&& other) noexcept = default;
        virtual ~Canvas() = default;

        void Initialize(const Manager::Resource::Loader& loader);
        void Update(float deltaMetaTime, float deltaGameTime) const;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) const;
        void Render(const Manager::Render::Renderer& renderer, Math::Rect baseRect) const;
        void Finalize() const;

        [[nodiscard]] std::shared_ptr<UI::Panel::Anchor> GetRootPanel() const;

    protected:
        virtual void OnCreateUserInterface();
        virtual void OnSetup();

        std::shared_ptr<UI::Panel::Anchor> _rootPanel;
    };
}
