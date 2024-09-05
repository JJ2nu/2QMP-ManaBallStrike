#pragma once

namespace Engine::UI::Panel
{
    class Stack : public Base
    {
    public:
        class StackChild;
        enum class Orientation : uint8_t;

    private:
        template <typename T>
        using ChildPair = std::pair<std::shared_ptr<StackChild>, std::shared_ptr<T>>;

    public:
        explicit Stack(const Math::Vector2& size);

        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;
        void Finalize() override;

        void AddChild(const std::shared_ptr<StackChild>& child);

        template <typename T, typename... Args>
        ChildPair<T> CreateChild(Args&&... args)
        {
            std::shared_ptr<T> child = std::make_shared<T>(std::forward<Args>(args)...);
            std::shared_ptr<StackChild> stackChild = std::make_shared<StackChild>(child);
            AddChild(stackChild);
            return {stackChild, child};
        }

        void SetOrientation(Orientation orientation);

    private:
        std::vector<std::shared_ptr<StackChild>> _children;
        Orientation _orientation;

    public:
        enum class Orientation : uint8_t
        {
            Horizontal,
            Vertical
        };

        class StackChild
        {
        public:
            explicit StackChild(const std::shared_ptr<Base>& child);

            void Initialize(const Manager::Resource::Loader& loader) const;
            void Update(float deltaMetaTime, float deltaGameTime) const;
            void LazyUpdate(float deltaMetaTime, float deltaGameTime) const;
            Math::Vector2 Render(const Manager::Render::Renderer& renderer, Math::Rect baseRect) const;
            void Finalize() const;

        private:
            std::shared_ptr<Base> _child;
        };
    };
}
