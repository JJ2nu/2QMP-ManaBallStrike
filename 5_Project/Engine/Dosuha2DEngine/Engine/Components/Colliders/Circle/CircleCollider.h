#pragma once
#include "../Base/ColliderBase.h"

namespace Engine::Component::Collider
{
    class Circle : public Component::Circle, public Base
    {
    public:
        explicit Circle(Type type);
        explicit Circle(Type type,float radius);
        void Update(float deltaMetaTime, float deltaGameTime) override;

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;

        void DrawCollider(bool isRender = true);
        
        [[nodiscard]] ColliderShape GetShape() override;
        [[nodiscard]] Math::Vector2 GetShapeCenter() override;

    private:
        void UpdateCollider();

        bool _isRender;
        Math::Circle _collider;
    };
}
