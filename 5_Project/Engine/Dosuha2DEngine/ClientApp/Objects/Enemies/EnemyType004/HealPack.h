#pragma once

namespace Client::Object
{
    class HealPack : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        HealPack(const Engine::Math::Vector2& location);

        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::Collider::Circle> _circleCollider;
        std::shared_ptr<Engine::Component::Animation> _animationComponent;

        Engine::Math::Vector2 _location;
        float _healingRange;
        float _healingTime;
        float _heal;
        float _elapsedTime;
        float _reactivateTime;
    };
}