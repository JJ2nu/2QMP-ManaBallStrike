#include "pch.h"
#include "PoisonBomb.h"
#include "Objects/Player/ControlPlayer.h"
#include "Objects/Enemies/Enemies.h"
#include "Poison.h"

Client::Object::PoisonBomb::PoisonBomb(const Engine::Math::Vector2& location)
    : BombBase(location)
{
    const auto gimicSection = Manager::Config::GetSection(L"Gimic");
    _damageOnPlayer = gimicSection->GetFloat(L"ToxicAttack");
    _damageOnEnemy = _damageOnPlayer / 10.f;
}

void Client::Object::PoisonBomb::OnCreateComponent()
{
    BombBase::OnCreateComponent();
    _animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Object/Bomb/object_005.png", L"Resources/Animation/Object/Bomb/object_005.csv");
    _animationComponent->SetParentScene(_rootScene);

    _effectAnimation = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Object/Bomb/effect_004_1.png", L"Resources/Animation/Object/Bomb/effect_004.csv");
    _effectAnimation->SetParentScene(_rootScene);
}

void Client::Object::PoisonBomb::OnSetup()
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

void Client::Object::PoisonBomb::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    if (_isExploded && _explosionEffect)
    {
        _owner.lock()->CreateObject<Poison>(_rootScene.lock()->GetLocation())->
            Initialize(Engine::Manager::Resource::GetLoader());
    }
    BombBase::OnPostUpdate(deltaMetaTime, deltaGameTime);
}
