#pragma once

namespace Engine::Object
{
    class Base;
}

namespace Engine::Component
{
    class Base
    {
    public:
        Base();
        Base(const Base& other) = default;
        Base(Base&& other) noexcept = default;
        Base& operator=(const Base& other) = default;
        Base& operator=(Base&& other) noexcept = default;
        virtual ~Base() = default;

        virtual void Initialize(Manager::Resource::Loader loader);
        virtual void FixedUpdate(float interval);
        virtual void Update(float deltaMetaTime, float deltaGameTime);
        virtual void LazyUpdate(float deltaMetaTime, float deltaGameTime);
        virtual void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const;
        virtual void Finalize();

        void SetOwner(const std::weak_ptr<Object::Base>& owner);
        [[nodiscard]] std::weak_ptr<Object::Base> GetOwner() const;
        bool IsRenderable = true;

    protected:
        std::weak_ptr<Object::Base> _owner;
    };
}
