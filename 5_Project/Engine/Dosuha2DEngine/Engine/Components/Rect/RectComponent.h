#pragma once
#include "../../Scene/Scene.h"
#include "../Base/ComponentBase.h"

namespace Engine::Component
{
    class Rect : public Scene
    {
    public:
        explicit Rect(const Math::Vector2& size);

        void SetSize(const Math::Vector2& size);

    protected:
        void UpdateCenterTransform() override;

        Math::Vector2 _size;
    };
}
