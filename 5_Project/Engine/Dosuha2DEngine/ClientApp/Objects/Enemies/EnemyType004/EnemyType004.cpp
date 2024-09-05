#include "pch.h"
#include "EnemyType004.h"
#include "../../../Components/KnockBackMovement/KnockBackMovement.h"
#include "HealPack.h"

Client::Object::EnemyType004::EnemyType004(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene)
	: EnemyBase(location, targetScene), _deathMotion(false)
{
	const auto enemySection = Manager::Config::GetSection(L"Enemy");
	_enemyHp = enemySection->GetFloat(L"Enemy4Health");
	_attackPower = enemySection->GetFloat(L"Enemy4Attack", 20.f);
	_moveSpeed = enemySection->GetFloat(L"Enemy4Speed");

	AddTag(L"EnemyAttack", _attackPower);
}

void Client::Object::EnemyType004::OnCreateComponent()
{
	EnemyBase::OnCreateComponent();

	_animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/mon_004.png", L"Resources/Animation/Enemy/mon_004.csv");
	_animationComponent->SetParentScene(_rootScene);

	_deathAnimation = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/mon_004_1.png", L"Resources/Animation/Enemy/mon_004_b.csv");
	_deathAnimation->SetParentScene(_rootScene);

	_onEnemy4HitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_009.wav", Audio::ChannelGroupType::Effect, false);

}

void Client::Object::EnemyType004::OnSetup()
{
	EnemyBase::OnSetup();
	_roundRectCollider->SetSize({ 80.f, 50.f });
	_roundRectCollider->SetLocation(_roundRectCollider->GetLocation() + Engine::Math::Vector2(0, 20));
	_roundRectCollider->SetRadius(15.f);
	//_roundRectCollider->DrawCollider();
	_roundRectCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold& manifold)
		{
			if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Ball"))
			{
				const auto damage = otherObject->GetTag(L"Damage")->GetValue();
				OnHit(*damage, -manifold.collisionNormal);
			}
		});
	_animationComponent->SetScale({ 0.9f, 0.9f });
	_animationComponent->SetMotion(L"Move");
	_deathAnimation->SetLocation(_deathAnimation->GetLocation() + Engine::Math::Vector2(0, 20));
	_deathAnimation->SetMotion(L"Idle");
	_enemyShadow->SetScale({ 0.7f, 0.7f });
	_enemyShadow->SetLocation(_enemyShadow->GetLocation() + Engine::Math::Vector2(0, 60));
}

void Client::Object::EnemyType004::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	EnemyBase::OnPostUpdate(deltaMetaTime, deltaGameTime);

	Engine::Math::Vector2 distance = _targetScene.lock()->GetLocation() - _rootScene.lock()->GetLocation();

	if (_isDeath)
	{
		if (!_deathMotion)
		{
			_deathAnimation->SetMotion(L"Death");
			_deathMotion = true;
			if (distance.x < 0) _deathAnimation->SetMirror(true);
			else _deathAnimation->SetMirror(false);
			_owner.lock()->CreateObject<HealPack>(_rootScene.lock()->GetLocation())->
				Initialize(Engine::Manager::Resource::GetLoader());
			_elapsedTime = 0.3f;
		}
		return;
	}

	if (_elapsedTime < 0.001f)
	{
		_movementComponent->SetDirection({ Engine::Math::Helper::Random()(-1.f, 1.f), Engine::Math::Helper::Random()(-1.f, 1.f) });
	}

	_elapsedTime += deltaGameTime;
	if (_elapsedTime > 3.f)
	{
		_movementComponent->SetSpeed(0.f);
		if (_elapsedTime > 4.5f)
		{
			_elapsedTime = 0.f;
			_movementComponent->SetSpeed(_moveSpeed);
		}
	}

	if (_movementComponent->GetDirection().x < 0) _animationComponent->SetMirror(true);
	else _animationComponent->SetMirror(false);
}

void Client::Object::EnemyType004::TakeDamage(float Damage)
{
	EnemyBase::TakeDamage(Damage);
	_onEnemy4HitSfx->Play();
	_onEnemy4HitSfx->SetVolume(0.5f);

}

void Client::Object::EnemyType004::OnPostFinalize()
{
	_onEnemy4HitSfx->Stop();
	_onEnemy4HitSfx = nullptr;
}
