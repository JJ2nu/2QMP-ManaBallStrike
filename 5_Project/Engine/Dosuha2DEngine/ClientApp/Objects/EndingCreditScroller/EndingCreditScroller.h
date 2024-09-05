#pragma once

namespace Client
{
    namespace Component
    {
        class EventBindAnimation;
    }
    namespace Object
    {
        class EndingCreditScroller : public Engine::Object::Base
        {
        public:
            using Event = std::function<void()>;

            EndingCreditScroller();
            [[nodiscard]] const Engine::Math::Rect& GetBound() const override;


        protected:
            void OnPostUpdate(float d1, float d2) override;
            void OnCreateComponent() override;
            void OnSetup() override;

        private:
            std::shared_ptr<Engine::Component::Bound> _boundComponent;
            std::shared_ptr<Component::EventBindAnimation> _animation;
            std::shared_ptr<Engine::Component::Movement> _movement;

        };
    }
}