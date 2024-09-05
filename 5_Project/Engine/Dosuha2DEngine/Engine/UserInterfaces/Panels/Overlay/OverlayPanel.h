#pragma once

namespace Engine::UI::Panel
{
    class Overlay : public Base
    {
    public:
        class OverlayChild;

    private:
        template <typename T>
        using ChildPair = std::pair<std::shared_ptr<OverlayChild>, std::shared_ptr<T>>;

    public:
        explicit Overlay(const Math::Vector2& size);

        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;
        void Finalize() override;

        void AddChild(const std::shared_ptr<OverlayChild>& child);

        template <typename T, typename... Args>
        ChildPair<T> CreateChild(Args&&... args)
        {
            std::shared_ptr<T> child = std::make_shared<T>(std::forward<Args>(args)...);
            std::shared_ptr<OverlayChild> overlayChild = std::make_shared<OverlayChild>(child);
            AddChild(overlayChild);
            return {overlayChild, child};
        }

    private:
        std::vector<std::shared_ptr<OverlayChild>> _children;

    public:
        class OverlayChild
        {
        public:
            explicit OverlayChild(const std::shared_ptr<Base>& child);

            void Initialize(const Manager::Resource::Loader& loader) const;
            void Update(float deltaMetaTime, float deltaGameTime) const;
            void LazyUpdate(float deltaMetaTime, float deltaGameTime) const;
            void Render(const Manager::Render::Renderer& renderer, Math::Rect baseRect) const;
            void Finalize() const;

        private:
            std::shared_ptr<Base> _child;
        };
    };
}
