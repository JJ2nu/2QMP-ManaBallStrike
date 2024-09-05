#pragma once

namespace Client::Object
{

    class BombBase : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        BombBase(const Engine::Math::Vector2& location);

        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

        void Explosion();

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
        void OnPostFinalize() override;

        void UpdateBomb(float deltaGameTime);
        void ExplosionEffect();

        std::shared_ptr<Engine::Component::Collider::Circle> _circleCollider;
        std::shared_ptr<Engine::Component::Collider::Circle> _explodeCollider;
        std::shared_ptr<Engine::Component::Animation> _animationComponent;
        std::shared_ptr<Engine::Component::Animation> _effectAnimation;
        std::shared_ptr<Engine::Component::Bitmap> _bombShadow;
        std::unique_ptr<::Audio::ISound> _onExplosionSfx;

        bool _isExploded;
        bool _explosionEffect;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;

        bool _willExplode;
        float _elapsedTime;
        float _explosionInterval;
        Engine::Math::Vector2 _location;
    };
}