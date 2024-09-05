#pragma once
#include "../../Camera/Camera.h"

namespace Engine::Component
{
    class Camera : public Bound, public Engine::Camera
    {
    public:
        explicit Camera(const Math::Vector2& size);
        explicit Camera(const Math::Vector2& size, const Math::Rect& limit);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        [[nodiscard]] D2D1::Matrix3x2F GetCameraMatrix() const override;
        [[nodiscard]] const Math::Rect& GetCullingBound() const override;

        void SetLimit(const Math::Rect& limit);
        void SetSmoothDamp(bool value = true);
        void SetSmoothTime(float smoothTime);

    protected:
        void UpdateWorldTransform() override;
        void UpdateLimitedLocation();

    private:
        Math::Rect _limit;
        Math::Vector2 _calibratedLocation;

        bool _smoothDamp;
        Math::Vector2 _currentVelocity;
        Math::Vector2 _targetPosition;
        float _smoothTime;
    };
}
