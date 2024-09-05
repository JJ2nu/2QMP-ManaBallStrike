#pragma once

namespace Client::Object
{
    class EnemyExplosion : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        EnemyExplosion(const Engine::Math::Vector2& location);

        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
        void OnPostFinalize() override;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::Collider::Circle> _circleCollider;
        std::unique_ptr<::Audio::ISound> _enemyExplosionSfx;


        Engine::Math::Vector2 _location;
        float _destroyDelay;
        float _explosionRange;
        float _explodeDamage;
    };
}