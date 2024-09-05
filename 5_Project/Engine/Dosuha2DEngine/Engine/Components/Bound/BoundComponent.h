#pragma once

namespace Engine::Component
{
    class Bound : public Base, public Rect
    {
    public:
        Bound();
        explicit Bound(Math::Vector2 size);
        void Update(float deltaMetaTime, float deltaGameTime) override;
        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
        void DrawBound(bool isRender = true);

        [[nodiscard]] const Math::Rect& GetBound() const;

    protected:
        void UpdateBound();
        bool _isRender = false;
        Math::Rect _bound;
    };
}
