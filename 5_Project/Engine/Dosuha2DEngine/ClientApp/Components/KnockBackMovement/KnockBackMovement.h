#pragma once

namespace Client::Component
{
    class KnockBackMovement : public Engine::Component::Movement
    {
    public:
        explicit KnockBackMovement(const std::shared_ptr<Engine::Scene>& movableScene);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void KnockBack(const Engine::Math::Vector2& direction);

    protected:
        bool _isKnockBack;

    private:
        void UpdateKnockBack(float deltaTime);
        Engine::Math::Vector2 _knockBackDirection;
        float _knockBackDuration;
        float _knockBackElapsedTime;
        float _knockBackSpeedRatio;
    };
}
