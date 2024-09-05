#pragma once

namespace Engine::Math::Collision
{
    struct Manifold
    {
        Vector2 collisionPoint;
        Vector2 collisionNormal;
        float overlapAmount;
    };

    struct Collision
    {
        bool operator()(const Rect& collisionRect, const Rect& targetRect, Manifold* manifold) const;
        bool operator()(const Rect& collisionRect, const Circle& targetCircle, Manifold* manifold) const;
        bool operator()(const Rect& collisionRect, const Vector2& targetPoint, Manifold* manifold) const;
        bool operator()(const Rect& collisionRect, const RoundRect& targetRoundRect, Manifold* manifold) const;
        bool operator()(const Circle& collisionCircle, const Circle& targetCircle, Manifold* manifold) const;
        bool operator()(const Circle& collisionCircle, const Rect& targetRect, Manifold* manifold) const;
        bool operator()(const Circle& collisionCircle, const Vector2& targetPoint, Manifold* manifold) const;
        bool operator()(const Circle& collisionCircle, const RoundRect& targetRoundRect, Manifold* manifold) const;
        bool operator()(const Vector2& collisionPoint, const Vector2& targetPoint, Manifold* manifold) const;
        bool operator()(const Vector2& collisionPoint, const Rect& targetRect, Manifold* manifold) const;
        bool operator()(const Vector2& collisionPoint, const Circle& targetCircle, Manifold* manifold) const;
        bool operator()(const Vector2& collisionPoint, const RoundRect& targetRoundRect, Manifold* manifold) const;
        bool operator()(const RoundRect& collisionRoundRect, const Vector2& targetPoint, Manifold* manifold) const;
        bool operator()(const RoundRect& collisionRoundRect, const Circle& targetCircle, Manifold* manifold) const;
        bool operator()(const RoundRect& collisionRoundRect, const Rect& targetRect, Manifold* manifold) const;
        bool operator()(const RoundRect& collisionRoundRect, const RoundRect& targetRoundRect, Manifold* manifold) const;

    private:
        float _epsilon = 1.0e-5f;
    };
}
