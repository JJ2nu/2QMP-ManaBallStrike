#pragma once

namespace Client::Component
{
    class KnockBackMovement;
}

namespace Client::Object
{
    class EnemyBase : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        EnemyBase(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene);

        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

        virtual void OnHit(float damage, const Engine::Math::Vector2& direction);
        void Poisoned();

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
        void OnPreFinalize() override;

        virtual void TakeDamage(float damage);
        virtual void Attack();
        void ExplosionEffect();

        std::shared_ptr<Engine::Component::Collider::RoundRect> _roundRectCollider;
        std::shared_ptr<Component::KnockBackMovement> _movementComponent;
        std::shared_ptr<Engine::Component::Animation> _animationComponent;
        std::shared_ptr<Engine::Component::Animation> _effectAnimation;
        std::shared_ptr<Engine::Component::Collider::Circle> _explodeCollider;
        std::shared_ptr<Engine::Component::Bitmap> _enemyShadow;

        std::weak_ptr<Engine::Scene> _targetScene;
        float _afterSpawnTime;
        float _enemyHp;
        float _moveSpeed;
        float _attackPower;
        float _attackSpeed;
        float _accelerate;
        float _coolTime;
        float _elapsedTime;
        bool _isAttack;
        bool _isDeath;
        bool _deathEffect;
        float _explosionRange;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        Engine::Math::Vector2 _location;
    };
}
