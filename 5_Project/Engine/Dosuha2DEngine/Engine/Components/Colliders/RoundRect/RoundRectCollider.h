#pragma once
#include "../Base/ColliderBase.h"

namespace Engine::Component::Collider
{
    class RoundRect : public Component::RoundRect, public Base
    {
    public:
        explicit RoundRect(Type type);
        explicit RoundRect(Type type, const Math::Vector2& size, float radius);
        void Update(float deltaMetaTime, float deltaGameTime) override;

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;

        void DrawCollider(bool isRender = true);
        [[nodiscard]] ColliderShape GetShape() override;
        [[nodiscard]] Math::Vector2 GetShapeCenter() override;

    protected:
        void UpdateCollider();

        bool _isRender;
        Math::RoundRect _collider;
    };
}
