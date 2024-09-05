#pragma once

#include "../../RoundRect/RoundRectComponent.h"

namespace Engine::Component::Shape
{
    class RoundRect : public Base, public Component::RoundRect, public Colored
    {
    public:
        explicit RoundRect(const Math::Vector2& size, float radius, D2D1_COLOR_F color);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
    };
}
