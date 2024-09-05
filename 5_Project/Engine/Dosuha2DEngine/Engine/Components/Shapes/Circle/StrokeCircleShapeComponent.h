#pragma once
#include "../Stroked/Stroked.h"

namespace Engine::Component::Shape
{
    class StrokeCircle : public Circle, public Stroked
    {
    public:
        StrokeCircle(float radius, D2D1_COLOR_F color, float strokeWidth = 1.0f);

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
    };
}
