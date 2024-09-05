#pragma once
#include "../Base/ColliderBase.h"

namespace Engine::Component::Collider
{
    class Box : public Rect, public Base
    {
    public:
        explicit Box(Type type);
        explicit Box(Type type, const Math::Vector2& size);
        void Update(float deltaMetaTime, float deltaGameTime) override;

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;

        void DrawCollider(bool isRender = true);
        [[nodiscard]] ColliderShape GetShape() override;
        [[nodiscard]] Math::Vector2 GetShapeCenter() override;
        [[nodiscard]] const Math::Rect& GetBound();

    protected:
        void UpdateCollider();

        bool _isRender;
        Math::Rect _collider;
    };
}
