#pragma once

namespace Engine::Component
{
    class Movement : public Base
    {
    public:
        explicit Movement(const std::shared_ptr<Scene>& movableScene);
        explicit Movement(const std::shared_ptr<Scene>& movableScene, float speed);

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void SetSpeed(float speed);

        void SetDirection(const Math::Vector2& direction);
        
        Math::Vector2 GetDirection() const;

    protected:
        std::shared_ptr<Scene> _movableScene;
        float _speed;
        Math::Vector2 _direction;
    };
}
