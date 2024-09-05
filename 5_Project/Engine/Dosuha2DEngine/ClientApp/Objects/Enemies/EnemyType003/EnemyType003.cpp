#include "pch.h"
#include "EnemyType003.h"
#include "EnemyBullet.h"
#include "../../../Components/KnockBackMovement/KnockBackMovement.h"

Client::Object::EnemyType003::EnemyType003(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene)
	: EnemyBase(location, targetScene), _chargeTime(4.f), _isShot(false), _isAwayDirection(false)
{
	const auto enemySection = Manager::Config::GetSection(L"Enemy");
	_enemyHp = enemySection->GetFloat(L"Enemy3Health");
	_moveSpeed = enemySection->GetFloat(L"Enemy3Speed");
	_attackPower = enemySection->GetFloat(L"Enemy3Attack");
	_shootingCoolTime = enemySection->GetFloat(L"Enemy3AttackCoolTime", 5.f);

	AddTag(L"EnemyAttack", _attackPower);
}

void Client::Object::EnemyType003::OnCreateComponent()
{
	EnemyBase::OnCreateComponent();

	_animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/mon_003.png", L"Resources/Animation/Enemy/mon_003.csv");
	_animationComponent->SetParentScene(_rootScene);
	_onEnemy3HitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_008.wav", Audio::ChannelGroupType::Effect, false);
	_onEnemy3FireSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_033	.wav", Audio::ChannelGroupType::Effect, false);

}

void Client::Object::EnemyType003::OnSetup()
{
	EnemyBase::OnSetup();
	_animationComponent->SetScale({ 0.8f, 0.8f });
	_roundRectCollider->SetSize({ 80.f, 35.f });
	_roundRectCollider->SetLocation(_roundRectCollider->GetLocation() + Engine::Math::Vector2(0, 30));
	_roundRectCollider->SetRadius(15.f);
	_roundRectCollider->DrawCollider(false);
	_enemyShadow->SetScale({ 0.7f, 0.7f });
	_enemyShadow->SetLocation(_enemyShadow->GetLocation() + Engine::Math::Vector2(0, 55));
}

void Client::Object::EnemyType003::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	EnemyBase::OnPostUpdate(deltaMetaTime, deltaGameTime);
	if (_isDeath) return;

	if (_elapsedTime <= _moveSpeed) _elapsedTime += deltaGameTime * _accelerate;
	else _elapsedTime = _moveSpeed;

	_movementComponent->SetSpeed(_elapsedTime);

	Engine::Math::Vector2 distance = _targetScene.lock()->GetLocation() - _rootScene.lock()->GetLocation();

	if (distance.x < 0)
	{
		_animationComponent->SetMirror(true);
		_isAwayDirection = false;
	}
	else
	{
		_animationComponent->SetMirror(false);
		_isAwayDirection = true;
	}

	if (distance.Magnitude() <= 250.f)
	{
		_movementComponent->SetDirection(-distance);
		_animationComponent->SetMirror(_isAwayDirection);
	}
	else if (distance.Magnitude() < 400.f && distance.Magnitude() > 250.f) _movementComponent->SetSpeed(0.f);
	else if (distance.Magnitude() >= 400.f) _movementComponent->SetDirection(distance);

	if (!_isShot)
	{
		_chargeTime += deltaGameTime;
		if (_chargeTime >= _shootingCoolTime)
		{
			Shoot();
		}
	}
	else
	{
		_chargeTime += deltaGameTime;
		if (_chargeTime >= 1.0f)
		{
			_isShot = false;
			_chargeTime = 0.f;
			_animationComponent->SetMotion(L"Move");
		}
	}

	if (_isAttack)
	{
		_coolTime += deltaGameTime;
		if (_coolTime >= _attackSpeed)
		{
			_isAttack = false;
			_coolTime = 0.f;
			_movementComponent->SetSpeed(_moveSpeed);
			_animationComponent->SetMotion(L"Move");
		}
	}
}

void Client::Object::EnemyType003::Shoot()
{

	_onEnemy3FireSfx->Play();
	_onEnemy3FireSfx->SetVolume(0.5f);

	Engine::Math::Vector2 location = _rootScene.lock()->GetLocation();
	GetOwner().lock()->CreateObject<EnemyBullet>(location, _targetScene.lock()->GetLocation() - location)->
		Initialize(Engine::Manager::Resource::GetLoader());
	_movementComponent->SetSpeed(0.f);
	_elapsedTime = 0.f;
	_isShot = true;
	_chargeTime = 0.f;
	_animationComponent->SetMotion(L"Attack");
}



void Client::Object::EnemyType003::TakeDamage(float Damage)
{
	EnemyBase::TakeDamage(Damage);
	_onEnemy3HitSfx->Play();
	_onEnemy3HitSfx->SetVolume(0.5f);

}

void Client::Object::EnemyType003::OnPostFinalize()
{
	_onEnemy3HitSfx->Stop();
	_onEnemy3HitSfx = nullptr;
	_onEnemy3FireSfx->Stop();
	_onEnemy3FireSfx = nullptr;
}
