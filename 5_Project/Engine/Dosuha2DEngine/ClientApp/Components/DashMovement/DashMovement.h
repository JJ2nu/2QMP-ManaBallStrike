#pragma once
#include "../KnockBackMovement/KnockBackMovement.h"

namespace Client::Component
{
    class DashMovement : public KnockBackMovement
    {
    public:
        explicit DashMovement(const std::shared_ptr<Engine::Scene>& movableScene);
        void Update(float deltaMetaTime, float deltaGameTime) override;

        bool Dash();
        bool IsDashing() const;

    protected:
        void UpdateColling(float deltaTime);
        void UpdateDash(float deltaTime);
    private:
        float _dashDuration;
        float _elapsedTime;
        float _speedRatio;
        Engine::Math::Vector2 _dashDirection;
        bool _isDashing;
        float _dashCoolTime;
        bool _isCooling;
    };
}
