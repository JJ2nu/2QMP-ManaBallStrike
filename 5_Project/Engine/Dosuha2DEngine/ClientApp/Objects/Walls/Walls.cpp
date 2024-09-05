#include "pch.h"
#include "Walls.h"

Client::Object::Wall::Wall()
{
    AddTag(L"Bouncing");
    AddTag(L"Wall");
}

const Engine::Math::Rect& Client::Object::Wall::GetBound() const
{
    return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::Wall::GetColliders() const
{
    return {_boxCollider};
}

void Client::Object::Wall::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _boxCollider = CreateComponent<Engine::Component::Collider::Box>(
        Engine::Component::Collider::Base::Type::Block);
    _boxCollider->SetParentScene(_rootScene);


    _shadow = CreateComponent<Engine::Component::Shadow>(Engine::Component::ShadowType::Box);
    _shadow->SetParentScene(_rootScene);
}

void Client::Object::Wall::OnSetup()
{
    _boxCollider->BindOnBeginBlock(
        [this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
        {
            OnBlock(other, manifold);
        });
}

void Client::Object::Wall::OnBlock(std::weak_ptr<Engine::Component::Base> other,
                                   Engine::Math::Collision::Manifold manifold)
{
}

void Client::Object::Wall::OnPostUpdate(float d1, float d2)
{
    _shadow->AddShadow();
};

void Client::Object::LeftWall::OnSetup()
{
    Wall::OnSetup();
    _rootScene.lock()->SetLocation({-780.f, 0.f});
    _boxCollider->SetSize({50.f, 1100.f});
    _shadow->SetSize(_boxCollider->GetBound().GetRightBottom());
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::TopWall::GetColliders() const
{
    auto parentColliders = Wall::GetColliders();
    parentColliders.push_back(_boxCollider2);
    return parentColliders;
}

void Client::Object::TopWall::OnSetup()
{
    Wall::OnSetup();

    _rootScene.lock()->SetLocation({0.f, -440.f});
    _boxCollider->SetSize({855.f, 50.f});
    _boxCollider->SetLocation({-500, 0});
   // _boxCollider->DrawCollider();

    _boxCollider2->SetSize({855.f, 50.f});
    _boxCollider2->SetLocation({500, 0});
   // _boxCollider2->DrawCollider();
    _boxCollider2->BindOnBeginBlock(
        [this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
        {
            OnBlock(other, manifold);
        });
    _shadow->SetSize({_boxCollider->GetBound().GetRightBottom().x * 1.2f, 200.f});
    _shadow->SetLocation({-600, -15});

	_shadow2->SetSize({ _boxCollider->GetBound().GetRightBottom().x * 1.2f, 200.f });
    _shadow2->SetLocation({600, -15});
}

void Client::Object::TopWall::OnCreateComponent()
{
    Wall::OnCreateComponent();

    _boxCollider2 = CreateComponent<Engine::Component::Collider::Box>(
        Engine::Component::Collider::Base::Type::Block);
    _boxCollider2->SetParentScene(_rootScene);
    _shadow2 = CreateComponent<Engine::Component::Shadow>(Engine::Component::ShadowType::Box);
    _shadow2->SetParentScene(_rootScene);
}

void Client::Object::TopWall::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    Wall::OnPostUpdate(deltaMetaTime, deltaGameTime);
    _shadow2->AddShadow();
}

void Client::Object::RightWall::OnSetup()
{
    Wall::OnSetup();
    _rootScene.lock()->SetLocation({780.f, 0.f});
    _boxCollider->SetSize({50.f, 1100.f});

    _shadow->SetSize(_boxCollider->GetBound().GetRightBottom());
}

void Client::Object::BottomWall::OnSetup()
{
    _rootScene.lock()->SetLocation({0.f, 520.f});
    _boxCollider->SetSize({1600.f, 50.f});

    _shadow->SetSize(_boxCollider->GetBound().GetRightBottom());
    Wall::OnSetup();
}
