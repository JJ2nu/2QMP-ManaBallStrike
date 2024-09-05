#pragma once

namespace Engine
{
    namespace Component::Collider
    {
        class Base;
    }

    class Collisionable
    {
    public:
        using ColliderShape = std::variant<Math::Rect, Math::Circle>;
        explicit Collisionable();
        Collisionable(const Collisionable& other) = default;
        Collisionable(Collisionable&& other) noexcept = default;
        Collisionable& operator=(const Collisionable& other) = default;
        Collisionable& operator=(Collisionable&& other) noexcept = default;
        virtual ~Collisionable() = default;

        [[nodiscard]] virtual std::vector<std::shared_ptr<Component::Collider::Base>> GetColliders() const = 0;

        void Release();
        [[nodiscard]] bool GetWillRelease() const;

    private:
        bool _willRelease;
    };
}
