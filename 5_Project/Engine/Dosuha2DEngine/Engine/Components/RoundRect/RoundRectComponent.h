#pragma once
#include "../../Scene/Scene.h"

namespace Engine::Component
{
    class RoundRect : public Scene
    {
    public:
        explicit RoundRect(const Math::Vector2& size, float radius);

        void SetSize(const Math::Vector2& size);
        void SetRadius(float radius);

    protected:
        void UpdateCenterTransform() override;

        Math::Vector2 _size;
        float _radius;
    };
}
