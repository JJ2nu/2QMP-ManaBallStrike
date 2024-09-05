#pragma once

namespace Engine::UI::Panel
{
    class Anchor : public Base
    {
    public:
        class AnchorChild;

    private:
        template <typename T>
        using ChildPair = std::pair<std::shared_ptr<AnchorChild>, std::shared_ptr<T>>;

    public:
        explicit Anchor(const Math::Vector2& size);

        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;
        void Finalize() override;

        void AddChild(const std::shared_ptr<AnchorChild>& child);

        template <typename T, typename... Args>
        ChildPair<T> CreateChild(Args&&... args)
        {
            std::shared_ptr<T> child = std::make_shared<T>(std::forward<Args>(args)...);
            std::shared_ptr<AnchorChild> anchorChild = std::make_shared<AnchorChild>(child);
            AddChild(anchorChild);
            return {anchorChild, child};
        }

    private:
        std::vector<std::shared_ptr<AnchorChild>> _children;

    public:
        class AnchorChild
        {
        public:
            enum class HorizontalAnchoring;
            enum class VerticalAnchoring;
            explicit AnchorChild(const std::shared_ptr<Base>& child);

            void Initialize(const Manager::Resource::Loader& loader) const;
            void Update(float deltaMetaTime, float deltaGameTime) const;
            void LazyUpdate(float deltaMetaTime, float deltaGameTime) const;
            void Render(const Manager::Render::Renderer& renderer, Math::Rect baseRect) const;
            void Finalize() const;

            [[nodiscard]] std::pair<HorizontalAnchoring, VerticalAnchoring> GetAnchoring() const;
            void SetAnchoring(HorizontalAnchoring horizontal, VerticalAnchoring vertical);

        private:
            std::shared_ptr<Base> _child;
            HorizontalAnchoring _horizontal;
            VerticalAnchoring _vertical;

        public:
            enum class HorizontalAnchoring
            {
                Left,
                Center,
                Right
            };
            enum class VerticalAnchoring
            {
                Top,
                Center,
                Bottom
            };
        };
    };
}
