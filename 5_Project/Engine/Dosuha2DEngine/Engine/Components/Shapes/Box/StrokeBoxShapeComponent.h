#pragma once
#include "BoxShapeComponent.h"
#include "../Stroked/Stroked.h"

namespace Engine::Component::Shape
{
    class StrokeBox : public Box, public Stroked
    {
    public:
        StrokeBox(const Math::Vector2& size, D2D1_COLOR_F color, float strokeWidth = 1.0f);

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
    };
}
