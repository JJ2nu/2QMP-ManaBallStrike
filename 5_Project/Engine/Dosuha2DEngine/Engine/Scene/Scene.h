#pragma once

namespace Engine
{
    class Scene
    {
    public:
        Scene();
        Scene(const Scene& other) = default;
        Scene(Scene&& other) noexcept = default;
        Scene& operator=(const Scene& other) = default;
        Scene& operator=(Scene&& other) noexcept = default;
        virtual ~Scene() = default;

        void SetParentScene(const std::weak_ptr<Scene>& parent);

        [[nodiscard]] Math::Vector2 GetLocation() const;
        [[nodiscard]] float GetRotation() const;
        void SetLocation(const Math::Vector2& location);
        void SetRotation(float rotation);
        Math::Vector2 GetScale() const;
        void SetScale(const Math::Vector2& scale);
        void SetCenter(const Math::Vector2& center);

        [[nodiscard]] D2D1::Matrix3x2F GetWorldTransform() const noexcept;
        [[nodiscard]] D2D1::Matrix3x2F GetCenterTransform() const noexcept;
        [[nodiscard]] D2D1::Matrix3x2F GetTranslationMatrix() const noexcept;
        [[nodiscard]] Math::Vector2 GetWorldLocation() const;

    protected:
        virtual void UpdateTransform();
        virtual void UpdateWorldTransform();
        virtual void UpdateCenterTransform() = 0;

        std::weak_ptr<Scene> _parentScene;

        Math::Vector2 _location;
        float _rotation;
        Math::Vector2 _scale;
        Math::Vector2 _center;

        D2D1::Matrix3x2F _translationMatrix;
        D2D1::Matrix3x2F _rotationMatrix;
        D2D1::Matrix3x2F _scaleMatrix;
        D2D1::Matrix3x2F _transform;
        D2D1::Matrix3x2F _worldTransform;
        D2D1::Matrix3x2F _centerTransform;
    };
}
