#pragma once
#include "../../Camera/Camera.h"
#include "../Base/ObjectBase.h"

namespace Engine::Object
{
    class Camera : public Base, public Engine::Camera
    {
    public:
        explicit Camera(const Math::Vector2& size);

        [[nodiscard]] D2D1::Matrix3x2F GetCameraMatrix() const override;
        [[nodiscard]] const Math::Rect& GetCullingBound() const override;
        [[nodiscard]] const Math::Rect& GetBound() const override;

    protected:
        void OnCreateComponent() override;

    private:
        Math::Vector2 _size;
        std::shared_ptr<Component::Camera> _cameraComponent;
    };
}
