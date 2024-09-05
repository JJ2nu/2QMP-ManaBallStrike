#pragma once

namespace Client
{
    namespace Component
    {
        class EventBindAnimation;
    }
    namespace Object
    {
        class Title : public Engine::Object::Base, public Engine::Collisionable
        {
        public:
            using Event = std::function<void()>;
        
            static constexpr std::wstring Tag = L"Title";

            Title();
            [[nodiscard]] const Engine::Math::Rect& GetBound() const override;

            [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

            void BindOnDamaged(Event event);

        protected:
            void OnCreateComponent() override;
            void OnSetup() override;

        private:
            std::shared_ptr<Engine::Component::Bound> _boundComponent;
            std::shared_ptr<Component::EventBindAnimation> _animation;
            std::shared_ptr<Engine::Component::AlphaBitmap> _bitmapComponent;
            std::shared_ptr<Engine::Component::Collider::Box> _boxCollider;

            Event _onDamaged;
            int _level;
        };
    }
}