#include "pch.h"
#include "Boss.h"
#include "Objects/Player/ControlPlayer.h"
#include "Objects/Ball/Ball.h"
#include "../../../Components/KnockBackMovement/KnockBackMovement.h"
#include <Objects/Effect/Effect.h>
#include "BossBullet.h"

Client::Object::Boss::Boss(const Engine::Math::Vector2& location)
	: EnemyBase(location, nullptr), _isRushing(false), _rushTargetPosition{ 0, 0 }, _t(0), _lockedTarget{ 0, 0 }, _invulnerableTimer(0.f), _shootingSound(false),
	_phase(1), _rushChargeTime(0), _isShooting(false), _shootingTime(0), _shootingNum(0), _isTargetLocked(false), _adjustValue(50.f), _soundDelay(0.f),
	_angleOffset(5.f), _circularAngleOffset(24.f), _patternProbabilities{ {0, 0.3f}, {1, 0.2f}, {2, 0.4f}, {3, 0.1f} }, _isInvulnerable(false)
{
	const auto enemySection = Manager::Config::GetSection(L"Enemy");
	_enemyHp = enemySection->GetFloat(L"BossHealth");
	_moveSpeed = enemySection->GetFloat(L"BossSpeed");
	_attackPower = enemySection->GetFloat(L"BossAttack");
	_attackSpeed = enemySection->GetFloat(L"BossAttackSpeed");
	_attackCoolTime = enemySection->GetFloat(L"BossAttackCoolTime");
	_phaseHp = _enemyHp;
	_patternTime = _attackCoolTime - 2.0f;

	AddTag(L"Boss");
	AddTag(L"EnemyAttack", _attackPower);
}

void Client::Object::Boss::OnCreateComponent()
{
	EnemyBase::OnCreateComponent();

	_animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/mon_005.png", L"Resources/Animation/Enemy/mon_005.csv");
	_animationComponent->SetParentScene(_rootScene);

	_onBossHitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_007_1.wav", Audio::ChannelGroupType::Effect, false);
	_onCircularShootSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_034_2.wav", Audio::ChannelGroupType::Effect, false);
	_onShootSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_034_1.wav", Audio::ChannelGroupType::Effect, false);
	_onAttackSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_030.wav", Audio::ChannelGroupType::Effect, false);
}

void Client::Object::Boss::OnSetup()
{
	EnemyBase::OnSetup();
	_roundRectCollider->SetSize({ 180.f, 100.f });
	_roundRectCollider->SetLocation(_roundRectCollider->GetLocation() + Engine::Math::Vector2(0, 40));
	_roundRectCollider->SetRadius(25.f);
	_roundRectCollider->DrawCollider(false);
	_roundRectCollider->Deactivate();
	_animationComponent->SetMotion(L"Idle");
	_onAttackSfx->Play();
	_onAttackSfx->SetVolume(0.7f);
	_enemyShadow->SetScale({ 1.2f, 1.2f });
	_enemyShadow->SetLocation(_enemyShadow->GetLocation() + Engine::Math::Vector2(0, 90));
}

void Client::Object::Boss::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	EnemyBase::OnPostUpdate(deltaMetaTime, deltaGameTime);
	if (_isDeath) return;

	if (_isInvulnerable)
	{
		_invulnerableTimer -= deltaGameTime;
		if (_invulnerableTimer <= 0)
		{
			_isInvulnerable = false;
		}
	}

	if (!_isRushing)
	{
		Engine::Math::Vector2 distance = _targetScene.lock()->GetLocation() - _rootScene.lock()->GetLocation();

		if (distance.x < 0) _animationComponent->SetMirror(true);
		else _animationComponent->SetMirror(false);

		_patternTime += deltaGameTime;
		if (_patternTime >= _attackCoolTime)
		{
			_roundRectCollider->Activate();
			_patternTime = 0.f;
			int pattern = ChoosePattern();
			PatternAttack(pattern, deltaGameTime, distance);
		}

		if (_isShooting)
		{
			Shoot(deltaGameTime, distance);
		}

		if (_enemyHp <= (_phaseHp * 0.7f) && _enemyHp > (_phaseHp * 0.4f)) PhaseTwo();
		else if (_enemyHp <= (_phaseHp * 0.4f)) PhaseThree();

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
	else
	{
		Rush(deltaGameTime);
	}
}

void Client::Object::Boss::OnPostFinalize()
{
	_onBossHitSfx->Stop();
	_onCircularShootSfx->Stop();
	_onShootSfx->Stop();
	_onAttackSfx->Stop();
	_onBossHitSfx = nullptr;
	_onCircularShootSfx = nullptr;
	_onShootSfx = nullptr;
	_onAttackSfx = nullptr;
	Manager::Data::DecreaseMonsterCount();
}

void Client::Object::Boss::TakeDamage(float Damage)
{
	if (!_isInvulnerable)
	{
		_animationComponent->SetMotion(L"Idle");
		EnemyBase::TakeDamage(Damage);
		_isInvulnerable = true;
		_invulnerableTimer = 1.0f;
		_onBossHitSfx->Play();
		_onBossHitSfx->SetVolume(0.5f);
		_patternTime = _attackCoolTime - 0.5f;
	}
}

void Client::Object::Boss::PatternAttack(int pattern, float deltaGameTime, const Engine::Math::Vector2& distance)
{
	switch (pattern)
	{
	case 0:
		_isShooting = true;
		_movementComponent->SetDirection({ 0, 0 });
		_animationComponent->SetMotion(L"Attack");
		_elapsedTime = 0.f;
		break;
	case 1:
		CircularShoot(deltaGameTime, distance);
		_animationComponent->SetMotion(L"Attack");
		_elapsedTime = 0.f;
		break;
	case 2:
		_rushIndicator = _owner.lock()->CreateObject<Client::Object::RushIndicator>(_rootScene.lock()->GetLocation(), _targetScene.lock()->GetLocation() + distance * 0.5f, L"Resources/Sprites/Enemy/mon_002_1.png");
		_rushIndicator->Initialize(Engine::Manager::Resource::GetLoader());
		_isRushing = true;
		_movementComponent->SetSpeed(1.0f);
		_elapsedTime = 0.f;
		_rushChargeTime = 0.f;
		if (_rootScene.lock()->GetLocation().Magnitude() > 250.f) _rushTargetPosition = { 0, 0 };
		else _rushTargetPosition = _targetScene.lock()->GetLocation() + distance * 0.5f;
		if (_rushIndicator)_rushIndicator->UpdateTargetLocation(_rushTargetPosition);
		_animationComponent->SetMotion(L"Move");
		break;
	case 3:
		_movementComponent->SetDirection(Engine::Math::Vector2::UnitVectorFromAngle(Engine::Math::Helper::Random()(0.f, 360.f)));
		_movementComponent->SetSpeed(_moveSpeed);
		_animationComponent->SetMotion(L"Move");
		_patternTime = _attackCoolTime - 2.f;
		break;
	}
}

void Client::Object::Boss::Shoot(float deltaGameTime, const Engine::Math::Vector2& distance)
{
	_soundDelay += deltaGameTime;
	if (!_isTargetLocked)
	{
		_lockedTarget = distance.Normalize();
		_isTargetLocked = true;
	}
	_shootingTime += deltaGameTime;
	if (_shootingTime >= 0.25f)
	{
		float angleOffset = Engine::Math::Helper::Random()(-_angleOffset, _angleOffset);
		Engine::Math::Vector2 adjustedDirection = _lockedTarget.Rotate(angleOffset);

		if (!_shootingSound && _soundDelay > 0.25f)
		{
			_onShootSfx->Play();
			_onShootSfx->SetVolume(0.2f);
			_shootingSound = true;
		}

		_owner.lock()->CreateObject<BossBullet>(_rootScene.lock()->GetLocation(), adjustedDirection)
			->Initialize(Engine::Manager::Resource::GetLoader());

		_shootingNum++;
		if (_shootingNum >= 5)
		{
			_isShooting = false;
			_shootingNum = 0;
			_isTargetLocked = false;
			_animationComponent->SetMotion(L"Move");
			_shootingSound = false;
			_soundDelay = 0.f;
		}

		_shootingTime = 0.f;
	}
}

void Client::Object::Boss::CircularShoot(float deltaGameTime, const Engine::Math::Vector2& distance)
{
	Engine::Math::Vector2 direction = distance.Normalize();

	float angleOffset = _circularAngleOffset;

	_onCircularShootSfx->Play();
	_onCircularShootSfx->SetVolume(0.2f);

	for (int i = 0; i < 5 * _phase; i++)
	{
		float angle = (i - 2) * angleOffset;
		Engine::Math::Vector2 adjustedDirection = direction.Rotate(angle);

		_owner.lock()->CreateObject<BossBullet>(_rootScene.lock()->GetLocation(), adjustedDirection)
			->Initialize(Engine::Manager::Resource::GetLoader());
	}
}

void Client::Object::Boss::Rush(float deltaGameTime)
{
	_elapsedTime += deltaGameTime;
	if (_elapsedTime >= 1.0f)
	{
		_t += deltaGameTime / _adjustValue;
		_t = Engine::Math::Helper::Min()(_t, 1.0f);
		Engine::Math::Vector2 position = _rootScene.lock()->GetLocation();
		Engine::Math::Vector2 newPosition = Engine::Math::Vector2::BezierInterpolate(position, (position + _rushTargetPosition) * 0.5f, _rushTargetPosition, _t);
		_rootScene.lock()->SetLocation(newPosition);
		if (_elapsedTime >= 2.5f)
		{
			_movementComponent->SetSpeed(_moveSpeed);
			_isRushing = false;
			_elapsedTime = 0.f;
			_t = 0.f;
		}
	}
}

void Client::Object::Boss::PhaseTwo()
{
	_attackCoolTime *= 0.8f;
	_phase = 2;
}

void Client::Object::Boss::PhaseThree()
{
	_attackCoolTime *= 0.5f;
	_attackSpeed *= 0.5f;
	_adjustValue *= 20.f;
	_moveSpeed *= 1.2f;
	_phase = 3;
}

int Client::Object::Boss::ChoosePattern()
{
	float value = Engine::Math::Helper::Random()(0.f, 1.f);

	float probability = 0.0f;
	for (const auto& pattern : _patternProbabilities)
	{
		probability += pattern.second;
		if (value <= probability)
			return pattern.first;
	}
}

void Client::Object::Boss::SetTargetScene(std::shared_ptr<Engine::Scene> targetScene)
{
	_targetScene = targetScene;
}

void Client::Object::Boss::OnHit(float damage, const Engine::Math::Vector2& direction)
{
	if (!_isRushing)
	{
		EnemyBase::OnHit(damage, direction);
	}
}
