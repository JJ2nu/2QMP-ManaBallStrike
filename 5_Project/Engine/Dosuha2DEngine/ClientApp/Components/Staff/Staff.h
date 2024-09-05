#pragma once

namespace Client::Component
{
    // TODO Change collider shape
    class Staff : public Engine::Component::Collider::Circle
    {
    public:
        using Event = std::function<void(Engine::Math::Vector2 ballLocation, size_t id)>;
        
        Staff(float range);

        void Initialize(Engine::Manager::Resource::Loader loader) override;
        void Update(float deltaMetaTime, float deltaGameTime) override;

        void Swing();

        void BindOnHit(const Event& event);
        void BindOnSmash(const Event& event);

    private:
        void HitBallCheck(const std::weak_ptr<Base>& ball, float overlapAmount);
        void HitEnemyCheck(const std::weak_ptr<Base>& enemy, const Engine::Math::Collision::Manifold& manifold);
        void HitBombCheck(const std::weak_ptr<Base>& bomb);
        void UpdateSwing();
        void UpdateSmash(float deltaTime);

        bool _isSwing;
        float _normalHitRange;
        float _knockBackRatio;
        Event _onHit;
        Event _onSmash;
        bool _canSmash;
        float _smashDelay;
        float _smashElapsedTime;
    };
}
