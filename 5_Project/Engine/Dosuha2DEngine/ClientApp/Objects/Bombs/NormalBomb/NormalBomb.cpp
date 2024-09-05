#include "pch.h"
#include "NormalBomb.h"
#include "Objects/Player/ControlPlayer.h"
#include "Objects/Enemies/Enemies.h"

Client::Object::NormalBomb::NormalBomb(const Engine::Math::Vector2& location)
    : BombBase(location), _damageOnPlayer(20.f), _damageOnEnemy(2.f)
{
}

void Client::Object::NormalBomb::OnCreateComponent()
{
    BombBase::OnCreateComponent();
    _animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Object/Bomb/object_002.png", L"Resources/Animation/Object/Bomb/object_002.csv");
    _animationComponent->SetParentScene(_rootScene);

    _effectAnimation = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Object/Bomb/effect_003_1.png", L"Resources/Animation/Object/Bomb/effect_003.csv");
    _effectAnimation->SetParentScene(_rootScene);
}

void Client::Object::NormalBomb::OnSetup()
{
    BombBase::OnSetup();
    _explodeCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold& manifold)
        {
            if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Enemy"))
            {
                const auto enemyObject = std::static_pointer_cast<Object::EnemyBase>(otherObject);
                enemyObject->OnHit(_damageOnEnemy, -manifold.collisionNormal);
            }
            if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Player"))
            {
                const auto playerObject = std::static_pointer_cast<Object::ControlPlayer>(otherObject);
                playerObject->OnHit(_damageOnPlayer, -manifold.collisionNormal);
            }
        });
    _effectAnimation->SetMotion(L"Idle");
    _effectAnimation->SetLocation(_effectAnimation->GetLocation() + Engine::Math::Vector2(0, -50));
}

void Client::Object::NormalBomb::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    BombBase::OnPostUpdate(deltaMetaTime, deltaGameTime);
}
