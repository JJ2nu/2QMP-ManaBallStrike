#pragma once
#include "../../Scene/Scene.h"
#include "../Base/ComponentBase.h"

namespace Engine::Component
{
    class RigidBody : public Base
    {
    public:
        explicit RigidBody(const std::weak_ptr<Engine::Scene>& rootScene, const float mass = 1.0f, const float restitution = 1.0f);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void AddForce(const Math::Vector2& force);
        void Reflect(const Math::Vector2& normal);

        void SetInitialVelocity(Math::Vector2 initialVelocity);
        void SetGravity(bool isGravity = true);
        void SetGravityScale(float scale);
        void SetMass(float mass);

        float GetMass() const;
        float GetRestitution() const;
        const Math::Vector2& GetVelocity() const;

    private:
        std::shared_ptr<Scene> _rootScene;
        Math::Vector2 _velocity;
        Math::Vector2 _maxVelocityValue;
        float _mass;        // 질량
        float _restitution; // 반발 계수(반사된 후의 속도 변화율 -> 0.0f <= r <= 1.0f)

        bool _activeGravity;
        float _gravityScale; // 중력 가속도
    };
}

