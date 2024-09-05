#include "pch.h"
#include "EnemyBase.h"
#include "../../../Components/KnockBackMovement/KnockBackMovement.h"
#include "../Explode/EnemyExplosion.h"

Client::Object::EnemyBase::EnemyBase(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene)
    : _targetScene(targetScene), _afterSpawnTime(0), _enemyHp(0), _moveSpeed(0), _attackPower(0),
      _attackSpeed(1.f), _accelerate(120.f), _coolTime(0), _elapsedTime(0), _isAttack(false), _isDeath(false), _deathEffect(false),
      _location(location)
{
    AddTag(L"Bouncing");
    AddTag(L"Enemy");
    const auto enemySection = Manager::Config::GetSection(L"Enemy");
    _explosionRange = enemySection->GetFloat(L"EnemyExplosionRange");
}

const Engine::Math::Rect& Client::Object::EnemyBase::GetBound() const
{
    return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::EnemyBase::GetColliders() const
{
    return {_roundRectCollider};
}

void Client::Object::EnemyBase::TakeDamage(const float damage)
{
    _enemyHp -= damage;
    if (_enemyHp <= 0 && !_isDeath)
    {
        _animationComponent->SetMotion(L"Death");
        _roundRectCollider->Deactivate();
        _isDeath = true;
        _elapsedTime = 0.f;
    }
}

void Client::Object::EnemyBase::Attack()
{
    if (!_isAttack) _isAttack = true;
    _animationComponent->SetMotion(L"Attack");
    _movementComponent->SetSpeed(0.f);
}

void Client::Object::EnemyBase::ExplosionEffect()
{
    _effectAnimation->SetMotion(L"Death");
}

void Client::Object::EnemyBase::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _effectAnimation = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/effect_003.png",
                                                                     L"Resources/Animation/Enemy/effect_003.csv");
    _effectAnimation->SetParentScene(_rootScene);

    _enemyShadow = CreateComponent<Engine::Component::Bitmap>(L"Resources/Sprites/Enemy/effect_016.png");
    _enemyShadow->SetParentScene(_rootScene);

    _roundRectCollider = CreateComponent<Engine::Component::Collider::RoundRect>(
        Engine::Component::Collider::Base::Type::Block);
    _roundRectCollider->SetParentScene(_rootScene);
    _roundRectCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other,
                                                const Engine::Math::Collision::Manifold& manifold)
    {
        if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Ball"))
        {
            const auto damage = otherObject->GetTag(L"Damage")->GetValue();
            OnHit(*damage, -manifold.collisionNormal);
        }
        if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Player"))
        {
            Attack();
        }
    });

    _movementComponent = CreateComponent<Component::KnockBackMovement>(_rootScene.lock());
    _explodeCollider = CreateComponent<Engine::Component::Collider::Circle>(
        Engine::Component::Collider::Base::Type::Block);
    _explodeCollider->SetParentScene(_rootScene);
}

void Client::Object::EnemyBase::OnSetup()
{
    _boundComponent->SetSize({100.f, 140.f});
    _rootScene.lock()->SetLocation(_location);
    _animationComponent->SetMotion(L"Move");
    _effectAnimation->SetMotion(L"Idle");
    _effectAnimation->SetLocation(_effectAnimation->GetLocation() + Engine::Math::Vector2(0, -50));
    _explodeCollider->Deactivate();
    _explodeCollider->SetRadius(_explosionRange * 0.5f);
    
    _roundRectCollider->BindOnBlock(
        [this](const std::weak_ptr<Engine::Component::Collider::Base>& other,
               const Engine::Math::Collision::Manifold& manifold)
        {
            if (other.lock()->GetOwner().lock()->FindTag(L"Wall"))
            {
                _rootScene.lock()->SetLocation(
                    _rootScene.lock()->GetLocation() + (manifold.collisionNormal * manifold.overlapAmount));
            }
        });
}

void Client::Object::EnemyBase::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    _renderOrder = GetBound().bottom;
    if (_isDeath)
    {
        //_explodeCollider->DrawCollider();
        _elapsedTime += deltaGameTime;
        if (!_deathEffect && _elapsedTime >= 0.7f)
        {
            ExplosionEffect();
            _deathEffect = true;
            _elapsedTime = 0.f;
            _owner.lock()->CreateObject<EnemyExplosion>(_rootScene.lock()->GetLocation())->
                   Initialize(Engine::Manager::Resource::GetLoader());
            // _explodeCollider->DrawCollider(false);
        }
        if (_deathEffect && _elapsedTime >= 1.0f)
        {
            Destroy();
            Release();
        }
    }
}

void Client::Object::EnemyBase::OnPreFinalize()
{
    Manager::Data::DecreaseMonsterCount();
    Base::OnPreFinalize();
}

void Client::Object::EnemyBase::OnHit(const float damage, const Engine::Math::Vector2& direction)
{
    TakeDamage(damage);
    _movementComponent->KnockBack(direction);
    _movementComponent->SetSpeed(0.f);
    _elapsedTime = 0;
}

void Client::Object::EnemyBase::Poisoned()
{
}

