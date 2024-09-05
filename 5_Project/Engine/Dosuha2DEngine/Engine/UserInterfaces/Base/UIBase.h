#pragma once

namespace Engine::UI
{
    class Base
    {
    public:
        explicit Base(const Math::Vector2& size);
        Base(const Base& other) = default;
        Base(Base&& other) noexcept = default;
        Base& operator=(const Base& other) = default;
        Base& operator=(Base&& other) noexcept = default;
        virtual ~Base() = default;

        virtual void Initialize(Manager::Resource::Loader loader);
        virtual void Update(float deltaMetaTime, float deltaGameTime);
        virtual void LazyUpdate(float deltaMetaTime, float deltaGameTime);
        virtual void Render(Manager::Render::Renderer renderer, Math::Rect baseRect);
        virtual void Finalize();

        void SetPadding(const Math::Rect& padding);
        void SetMargin(const Math::Rect& margin);

        [[nodiscard]] Math::Vector2 GetSize() const;
        void SetSize(const Math::Vector2& size);

    protected:
        Math::Rect GetChildRect(const Math::Rect& baseRect) const;
        
        Math::Rect _padding;
        Math::Rect _margin;
        Math::Vector2 _size;
    };
}
