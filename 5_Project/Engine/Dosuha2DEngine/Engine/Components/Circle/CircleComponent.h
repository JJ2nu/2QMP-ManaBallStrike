#pragma once

namespace Engine::Component
{
    class Circle : public Scene
    {
    public:
        explicit Circle(float radius);

        void SetRadius(float radius);

    protected:
        void UpdateCenterTransform() override;

        float _radius;
    };
}
