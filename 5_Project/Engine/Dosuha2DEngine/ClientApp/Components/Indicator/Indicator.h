#pragma once

namespace Client::Component
{
    class Indicator : public Engine::Component::Bitmap
    {
    public:
        Indicator();

        void Update(float deltaMetaTime, float deltaGameTime) override;

        void SetDirection(const Engine::Math::Vector2& direction);
        Engine::Math::Vector2 GetDirection() const;
        
    private:
        Engine::Math::Vector2 _direction;
    };
}
