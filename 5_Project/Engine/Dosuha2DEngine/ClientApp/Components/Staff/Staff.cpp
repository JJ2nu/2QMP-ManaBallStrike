#include "pch.h"
#include "Staff.h"

#include "Objects/Ball/Ball.h"
#include "Objects/Enemies/Enemies.h"
#include "Objects/Bombs/Bombs.h"

Client::Component::Staff::Staff(float range)
    : Circle(Type::Overlap, range), _isSwing(false), _normalHitRange(80.f), _knockBackRatio(10.f),
      _canSmash(true), _smashDelay(Manager::Config::GetSection(L"Player")->GetFloat(L"SmashDelay")),
      _smashElapsedTime(0.0f)
{
    Deactivate();
    //DrawCollider(true);
}

void Client::Component::Staff::Initialize(const Engine::Manager::Resource::Loader loader)
{
    Circle::Initialize(loader);
    BindOnBeginOverlap([this](const std::weak_ptr<Base>& other, const Engine::Math::Collision::Manifold& manifold)
    {
        if (IsActivated() && other.lock()->GetOwner().lock()->FindTag(L"Ball")) HitBallCheck(
            other, manifold.overlapAmount);
        if (IsActivated() && other.lock()->GetOwner().lock()->FindTag(L"Enemy") && !other.lock()->GetOwner().lock()->
            FindTag(L"Boss")) HitEnemyCheck(other, manifold);
        if (IsActivated() && other.lock()->GetOwner().lock()->FindTag(L"Bomb")) HitBombCheck(other);
    });
}

void Client::Component::Staff::Update(const float deltaMetaTime, const float deltaGameTime)
{
    Circle::Update(deltaMetaTime, deltaGameTime);
    UpdateSwing();
    UpdateSmash(deltaGameTime);
}

void Client::Component::Staff::Swing()
{
    Activate();
}

void Client::Component::Staff::BindOnHit(const Event& event)
{
    _onHit = event;
}

void Client::Component::Staff::BindOnSmash(const Event& event)
{
    _onSmash = event;
}

void Client::Component::Staff::HitBallCheck(const std::weak_ptr<Base>& ball, const float overlapAmount)
{
    const auto ballObject = std::static_pointer_cast<Object::Ball>(ball.lock()->GetOwner().lock());
    if (overlapAmount > _normalHitRange && _canSmash)
    {
        _onSmash(ballObject->GetLocation(), ballObject->GetId());
        _canSmash = false;
        _smashElapsedTime = 0.0f;
    }
    else _onHit(ballObject->GetLocation(), ballObject->GetId());
    ballObject->CancelOnDisappear();
    ballObject->Destroy();
    ballObject->Release();
    Deactivate();
}

void Client::Component::Staff::HitEnemyCheck(const std::weak_ptr<Base>& enemy,
                                             const Engine::Math::Collision::Manifold& manifold)
{
    const auto enemyObject = std::static_pointer_cast<Object::EnemyBase>(enemy.lock()->GetOwner().lock());
    enemyObject->OnHit(
        0.f, (manifold.collisionPoint - GetOwner().lock()->GetLocation() + manifold.collisionNormal).Normalize() *
        _knockBackRatio);
}

void Client::Component::Staff::HitBombCheck(const std::weak_ptr<Base>& bomb)
{
    const auto bombObject = std::static_pointer_cast<Object::BombBase>(bomb.lock()->GetOwner().lock());
    bombObject->Explosion();
}

void Client::Component::Staff::UpdateSwing()
{
    if (_isSwing) Deactivate();
    _isSwing = IsActivated();
}

void Client::Component::Staff::UpdateSmash(const float deltaTime)
{
    if (_canSmash) return;
    _smashElapsedTime += deltaTime;
    if (_smashElapsedTime < _smashDelay) return;
    _smashElapsedTime = 0.0f;
    _canSmash = true;
}
