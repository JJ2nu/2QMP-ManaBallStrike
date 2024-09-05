#pragma once

namespace Client::Object
{
    class EnemyBullet : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        EnemyBullet(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction);

        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

    protected:
        void OnPostUpdate(float delatMetatTime, float deltaGameTime) override;
        void OnCreateComponent() override;
        void OnSetup() override;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::Collider::Circle> _circleCollider;
        std::shared_ptr<Engine::Component::Movement> _movementComponent;
        std::shared_ptr<Engine::Component::Animation> _animationComponent;
        std::shared_ptr<Engine::Component::Bitmap> _bulletShadow;

        Engine::Math::Vector2 _location;
        Engine::Math::Vector2 _direction;
        float _attackPower;
        float _moveSpeed;
    };
}