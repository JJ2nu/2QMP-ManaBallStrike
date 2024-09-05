#include "pch.h"
#include "EnemyType002.h"
#include "../../../Components/KnockBackMovement/KnockBackMovement.h"
#include <Objects/Effect/Effect.h>


Client::Object::EnemyType002::EnemyType002(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene)
	: EnemyBase(location, targetScene), _isRushing(false), _elapsedTime(5.f), _rushSpeedRatio(50.f),
	_adjustedValue(0.4f), _rushTargetPosition(0, 0), _t(0), _rushAnimation(false)
{
	const auto enemySection = Manager::Config::GetSection(L"Enemy");
	_enemyHp = enemySection->GetFloat(L"Enemy2Health");
	_moveSpeed = enemySection->GetFloat(L"Enemy2Speed");
	_attackPower = enemySection->GetFloat(L"Enemy2Attack");
	_rushCoolTime = enemySection->GetFloat(L"Enemy2AttackCoolTime", 5.f);
	_rushCharge = _rushCoolTime;

	AddTag(L"EnemyAttack", _attackPower);
}

void Client::Object::EnemyType002::OnCreateComponent()
{
	EnemyBase::OnCreateComponent();

	_animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/mon_002.png", L"Resources/Animation/Enemy/mon_002.csv");
	_animationComponent->SetParentScene(_rootScene);

	_onEnemy2HitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_007_1.wav", Audio::ChannelGroupType::Effect, false);

}

void Client::Object::EnemyType002::OnSetup()
{
	EnemyBase::OnSetup();
	_roundRectCollider->SetSize({ 80.f, 50.f });
	_roundRectCollider->SetLocation(_roundRectCollider->GetLocation() + Engine::Math::Vector2(0, 20));
	_roundRectCollider->SetRadius(25.f);
	_roundRectCollider->DrawCollider(false);
	_enemyShadow->SetScale({ 0.6f, 0.6f });
	_enemyShadow->SetLocation(_enemyShadow->GetLocation() + Engine::Math::Vector2(0, 55));

}

void Client::Object::EnemyType002::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	EnemyBase::OnPostUpdate(deltaMetaTime, deltaGameTime);

	if (_isDeath) return;

	if (!_isRushing)
	{

		if (_elapsedTime <= _moveSpeed) _elapsedTime += deltaGameTime * _accelerate;
		else _elapsedTime = _moveSpeed;

		_movementComponent->SetSpeed(_elapsedTime);

		Engine::Math::Vector2 distance = _targetScene.lock()->GetLocation() - _rootScene.lock()->GetLocation();
		_movementComponent->SetDirection(distance);


		if (distance.x < 0) _animationComponent->SetMirror(true);
		else _animationComponent->SetMirror(false);

		_rushCharge += deltaGameTime;

		if (distance.Magnitude() < 400.f && _rushCharge >= _rushCoolTime)
		{
			_rushIndicator = _owner.lock()->CreateObject<Client::Object::RushIndicator>(_rootScene.lock()->GetLocation(), _rushTargetPosition, L"Resources/Sprites/Enemy/mon_002_1.png");
			_rushIndicator->Initialize(Engine::Manager::Resource::GetLoader());
			_isRushing = true;
			_movementComponent->SetSpeed(1.0f);
			_elapsedTime = 0.f;
			_rushCharge = 0.f;
			_rushTargetPosition = _targetScene.lock()->GetLocation() + distance * _adjustedValue;
			if (_rushIndicator)_rushIndicator->UpdateTargetLocation(_rushTargetPosition);
			_animationComponent->SetMotion(L"Rush");
		}
	}
	else
	{
		Rush(deltaGameTime);
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

void Client::Object::EnemyType002::Rush(float deltaGameTime)
{
	_elapsedTime += deltaGameTime;
	if (!_rushAnimation && _elapsedTime > 0.5f)
	{
		_animationComponent->SetMotion(L"Rush");
		_rushAnimation = true;
	}
	if (_elapsedTime >= 1.0f)
	{
		_t += deltaGameTime / _rushSpeedRatio;
		_t = Engine::Math::Helper::Min()(_t, 1.0f);
		Engine::Math::Vector2 position = _rootScene.lock()->GetLocation();
		Engine::Math::Vector2 newPosition = Engine::Math::Vector2::BezierInterpolate(position, (position + _rushTargetPosition) * 0.5f, _rushTargetPosition, _t);
		_rootScene.lock()->SetLocation(newPosition);
		if (_elapsedTime >= 2.5f)
		{
			_movementComponent->SetSpeed(_moveSpeed);
			_isRushing = false;
			_elapsedTime = 0.f;
			_rushAnimation = false;
			_t = 0.f;
			_animationComponent->SetMotion(L"Move");
		}
	}
}


void Client::Object::EnemyType002::TakeDamage(float Damage)
{
	EnemyBase::TakeDamage(Damage);
	_onEnemy2HitSfx->Play();
	_onEnemy2HitSfx->SetVolume(0.5f);

}

void Client::Object::EnemyType002::OnPostFinalize()
{
	_onEnemy2HitSfx->Stop();
	_onEnemy2HitSfx = nullptr;
}
