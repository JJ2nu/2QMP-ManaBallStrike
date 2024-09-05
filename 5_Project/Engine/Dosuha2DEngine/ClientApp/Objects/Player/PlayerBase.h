#pragma once

namespace Client
{
    namespace Component
    {
        class EventBindAnimation;
        class DashMovement;
    }

    namespace Object
    {
        class PlayerBase : public Engine::Object::Base, public Engine::Collisionable
        {
        public:
            PlayerBase(const Engine::Math::Rect& cameraLimit, float initialYLocation);
            [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
            std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

        protected:
            void OnCreateComponent() override;
            void OnSetup() override;
            void OnPostFinalize() override;

            virtual void ComponentSetup();
            virtual void AnimationSetup();
            virtual void DataSetup();

            void Move(const Engine::Math::Vector2& direction);
            void Stop();

            std::shared_ptr<Engine::Component::Bound> _boundComponent;
            std::shared_ptr<Component::EventBindAnimation> _animationComponent;
            std::shared_ptr<Component::DashMovement> _movementComponent;
            std::shared_ptr<Engine::Component::Collider::RoundRect> _roundRectCollider;
            std::shared_ptr<Engine::Component::Camera> _cameraComponent;
            std::shared_ptr<Engine::Component::Bitmap> _playerShadow;

            std::unique_ptr<::Audio::ISound> _walkSfx;

        private:
            std::shared_ptr<Engine::Component::Spotlight> _light;
            Engine::Math::Rect _cameraLimit;
            float _initialYLocation;
            bool _moveflag = false;
            int _speedRegister;
        };
    }
}
