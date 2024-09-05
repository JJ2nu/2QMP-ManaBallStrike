#pragma once

namespace Engine::Component
{
    class UI : public Base, public Rect
    {
    public:
        explicit UI(const Math::Vector2& size);

        void Initialize(Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void LazyUpdate(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
        void Finalize() override;
        
        [[nodiscard]] std::shared_ptr<Engine::UI::Panel::Anchor> GetRootPanel() const;

    protected:
        void UpdateWorldTransform() override;
        
        std::shared_ptr<Engine::UI::Panel::Anchor> _rootPanel;
    };
}
