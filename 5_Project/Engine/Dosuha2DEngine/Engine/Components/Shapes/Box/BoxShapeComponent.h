#pragma once
#include "../../Rect/RectComponent.h"

namespace Engine::Component::Shape
{
    class Box : public Base, public Rect, public Colored
    {
    public:
        explicit Box(const Math::Vector2& size, D2D1_COLOR_F color);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
    };
}
