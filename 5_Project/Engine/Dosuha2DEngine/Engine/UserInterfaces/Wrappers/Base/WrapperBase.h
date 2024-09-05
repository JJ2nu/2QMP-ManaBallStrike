#pragma once

namespace Engine::UI::Wrapper
{
    class Base : public UI::Base
    {
    public:
        explicit Base(const Math::Vector2& size);

        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, Math::Rect baseRect) override;
        void Finalize() override;

        void SetChild(const std::shared_ptr<UI::Base>& child);

        template <typename T, typename... Args>
        std::shared_ptr<T> CreateChild(Args&&... args)
        {
            auto child = std::make_shared<T>(std::forward<Args>(args)...);
            SetChild(child);
            return child;
        }

    protected:
        std::shared_ptr<UI::Base> _child;
    };
}
