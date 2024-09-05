#pragma once

namespace Client::Object
{
    class TestObject : public Engine::Object::Base
    {
    public:
        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;

    protected:
        void OnCreateComponent() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
        std::shared_ptr<Engine::Component::Animation> _animationComponent;
    };
}
