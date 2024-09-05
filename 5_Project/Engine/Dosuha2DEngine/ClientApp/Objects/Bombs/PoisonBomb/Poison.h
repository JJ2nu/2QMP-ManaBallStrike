#pragma once

namespace Client::Object
{
    class Poison : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        Poison(const Engine::Math::Vector2& location);

        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::Collider::Circle> _circleCollider;
        std::shared_ptr<Engine::Component::Collider::Circle> _enemyCheckCircleCollider;
        std::shared_ptr<Engine::Component::Animation> _animationComponent;

        Engine::Math::Vector2 _location;
        float _toxicRange;
        float _toxicTime;
        float _toxic;
        float _elapsedTime;
        float _reactivateTime;
        float _enemyCheckReactivateTime;
    };
}