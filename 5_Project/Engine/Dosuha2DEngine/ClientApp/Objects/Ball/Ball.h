#pragma once

namespace Client::Component
{
    class EventBindAnimation;
    class CollisionEffect;
    class TrailEffect;
}
namespace Client::Object
{
    class Ball : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        using Event = std::function<void()>;
        Ball();
        Ball(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction, float speedRatio, float damage, int reflectCount, size_t id);
        
        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

        void OnPostFinalize() override;

        void BindOnDisappear(const Event& event);
        void CancelOnDisappear();

        size_t GetId() const;

    protected:
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
        void OnCreateComponent() override;
        void OnSetup() override;
        void Bounce(const Engine::Math::Vector2& normal);
        void DecreaseReflectCount();
        bool _isTrailOn = false;
        
    private:
        size_t _id;
        
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        
        std::shared_ptr<Client::Component::EventBindAnimation> _manaBall;
        std::shared_ptr<Client::Component::EventBindAnimation> _manaParticle;
        std::shared_ptr<Client::Component::TrailEffect> _trailEffect;
        std::shared_ptr<Client::Component::CollisionEffect> _collisionEffect;

        std::shared_ptr<Engine::Component::Collider::Circle> _circleCollider;
        std::shared_ptr<Engine::Component::Movement> _movementComponent;
        std::shared_ptr<Engine::Component::Spotlight> _light;

        std::unique_ptr<::Audio::ISound> _ballBounceSfx;
        std::unique_ptr<::Audio::ISound> _chestHitSfx;
        std::unique_ptr<::Audio::ISound> _bookPileSfx;
        //std::unique_ptr<::Audio::ISound> _ballBounceSfx;



        int _reflectCount;

        Engine::Math::Vector2 _setupDirection;
        Engine::Math::Vector2 _setupLocation;
        float _speed;
        float _setupSpeedRatio;
        float _damage;

        Event _onDisappear;
        bool _isDisappearCancel;

        int _trailEffectIdx = 0;
        float _trailEffectElapsedTimer = 0.f;

    };


    class NormalBall : public Ball
    {
    public:
        NormalBall() = default;
        NormalBall(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction, size_t id);
    };

    class PerfectServeBall : public Ball
    {
    public:
        PerfectServeBall() = default;
        PerfectServeBall(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction, size_t id);
    };
    
    class HitBall : public Ball
    {
    public:
        HitBall() = default;
        HitBall(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction, size_t id);
    };

    class SmashBall : public Ball
    {
    public:
        SmashBall() = default;
        SmashBall(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction, size_t id);
    };
}
