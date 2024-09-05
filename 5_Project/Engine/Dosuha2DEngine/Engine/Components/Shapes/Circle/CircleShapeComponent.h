#pragma once
#include "../../Circle/CircleComponent.h"

namespace Engine::Component::Shape
{
    class Circle : public Base, public Component::Circle, public Colored
    {
    public:
        explicit Circle(float radius, D2D1_COLOR_F color);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void Render(Manager::Render::Renderer renderer, D2D1_MATRIX_3X2_F cameraMatrix) const override;
    };
}
