#pragma once

namespace Client::Object
{
    class Wall : public Engine::Object::Base, public Engine::Collisionable
    {
    public:
        static constexpr std::wstring_view Tag = L"Wall";

        Wall();
        [[nodiscard]] const Engine::Math::Rect& GetBound() const override;
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;

    protected:
        void OnCreateComponent() override;
        void OnSetup() override;

        void OnBlock(std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold);
        bool once = true;
        void OnPostUpdate(float d1, float d2) override;

        std::shared_ptr<Engine::Component::Collider::Box> _boxCollider;
        std::shared_ptr<Engine::Component::Shadow> _shadow;

    private:
        std::shared_ptr<Engine::Component::Bound> _boundComponent;
    };

    class LeftWall : public Wall
    {
    protected:
        void OnSetup() override;
    };

    class TopWall : public Wall
    {
    public:
        [[nodiscard]] std::vector<std::shared_ptr<Engine::Component::Collider::Base>> GetColliders() const override;
    protected:
        void OnSetup() override;
        void OnCreateComponent() override;
        void OnPostUpdate(float deltaMetaTime, float deltaGameTime) override;
        std::shared_ptr<Engine::Component::Collider::Box> _boxCollider2;
        std::shared_ptr<Engine::Component::Shadow> _shadow2;
    };

    class RightWall : public Wall
    {
    protected:
        void OnSetup() override;
    };

    class BottomWall : public Wall
    {
    protected:
        void OnSetup() override;
    };
}
