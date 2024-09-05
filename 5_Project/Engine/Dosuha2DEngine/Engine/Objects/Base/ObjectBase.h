#pragma once

namespace Engine
{
    class World;
    class Scene;

    namespace Component
    {
        class Base;
    }
}

namespace Engine::Object
{
    class Base : public std::enable_shared_from_this<Base>
    {
    public:
        Base(const Base& other) = default;
        Base(Base&& other) noexcept = default;
        Base& operator=(const Base& other) = default;
        Base& operator=(Base&& other) noexcept = default;
        virtual ~Base() = default;

        void Initialize(Manager::Resource::Loader loader);
        void FixedUpdate(float interval);
        void Update(float deltaMetaTime, float deltaGameTime);
        void LazyUpdate(float deltaMetaTime, float deltaGameTime);
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix);
        void Finalize();

        void SetOwner(const std::weak_ptr<World>& owner);
        void SetRootScene(const std::weak_ptr<Scene>& rootScene);

        Math::Vector2 GetLocation() const;

        [[nodiscard]] virtual const Math::Rect& GetBound() const = 0;

        void AddComponent(const std::shared_ptr<Component::Base>& component);

        std::weak_ptr<Scene> GetRootScene() const;
        std::weak_ptr<World> GetOwner() const;

        template <typename U, typename... Args> requires std::derived_from<U, Component::Base>
        std::shared_ptr<U> CreateComponent(Args&&... args)
        {
            std::shared_ptr<U> component = std::make_shared<U>(std::forward<Args>(args)...);
            AddComponent(component);
            return component;
        }

        [[nodiscard]] bool FindTag(std::wstring_view tagName) const;
        [[nodiscard]] std::optional<Tag> GetTag(std::wstring_view tagName) const;
        float GetRenderOrder() const;

        void Destroy();
        [[nodiscard]] bool GetWaitDestroy() const;
    protected:
        Base();
        virtual void OnCreateComponent();
        virtual void OnSetup();

        virtual void OnPreUpdate(float deltaMetaTime, float deltaGameTime);
        virtual void OnPostUpdate(float deltaMetaTime, float deltaGameTime);

        virtual void OnPreFinalize();
        virtual void OnPostFinalize();

        void AddTag(const Tag& tag);
        void AddTag(std::wstring_view name);
        void AddTag(std::wstring_view name, float value);

        std::weak_ptr<Scene> _rootScene;
        std::weak_ptr<World> _owner;
        float _renderOrder = (Engine::Manager::Window::GetSize().y / 2);

    private:
        std::vector<std::shared_ptr<Component::Base>> _components;
        bool _willDestroy;
        std::set<Tag> _tags;
    };
}
