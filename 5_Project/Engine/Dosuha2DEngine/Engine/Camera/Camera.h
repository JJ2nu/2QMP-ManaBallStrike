#pragma once

namespace Engine
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const Camera& other) = default;
        Camera(Camera&& other) noexcept = default;
        Camera& operator=(const Camera& other) = default;
        Camera& operator=(Camera&& other) noexcept = default;
        virtual ~Camera() = default;

        [[nodiscard]] virtual D2D1::Matrix3x2F GetCameraMatrix() const = 0;
        [[nodiscard]] virtual const Math::Rect& GetCullingBound() const = 0;
    };
}
