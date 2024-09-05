#include "pch.h"
#include "EnemyType001.h"
#include "Objects/Player/ControlPlayer.h"
#include "../../../Components/KnockBackMovement/KnockBackMovement.h"

Client::Object::EnemyType001::EnemyType001(const Engine::Math::Vector2& location, std::shared_ptr<Engine::Scene> targetScene)
	: EnemyBase(location, targetScene)
{
	const auto enemySection = Manager::Config::GetSection(L"Enemy");
	_enemyHp = enemySection->GetFloat(L"Enemy1Health");
	_moveSpeed = enemySection->GetFloat(L"Enemy1Speed");
	_attackPower = enemySection->GetFloat(L"Enemy1Attack");

	AddTag(L"EnemyAttack", _attackPower);
}

void Client::Object::EnemyType001::OnCreateComponent()
{
	EnemyBase::OnCreateComponent();

	_animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/mon_001.png", L"Resources/Animation/Enemy/mon_001.csv");
	_animationComponent->SetParentScene(_rootScene);
	_onEnemy1HitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_006.wav", Audio::ChannelGroupType::Effect, false);
}

void Client::Object::EnemyType001::OnSetup()
{
	EnemyBase::OnSetup();
	_roundRectCollider->SetSize({ 75.f, 50.f });
	_roundRectCollider->SetLocation(_roundRectCollider->GetLocation() + Engine::Math::Vector2(-3, 25));
	_roundRectCollider->SetRadius(20.f);
	_roundRectCollider->DrawCollider(false);
	_enemyShadow->SetScale({ 0.7f, 0.7f });
	_enemyShadow->SetLocation(_enemyShadow->GetLocation() + Engine::Math::Vector2(-3, 70));
}

void Client::Object::EnemyType001::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	EnemyBase::OnPostUpdate(deltaMetaTime, deltaGameTime);
	if (_isDeath) return;

	if (_elapsedTime <= _moveSpeed) _elapsedTime += deltaGameTime * _accelerate;
	else _elapsedTime = _moveSpeed;

	_movementComponent->SetSpeed(_elapsedTime);

	Engine::Math::Vector2 distance = _targetScene.lock()->GetLocation() - _rootScene.lock()->GetLocation();
	_movementComponent->SetDirection(distance);

	if (distance.x < 0) _animationComponent->SetMirror(true);
	else _animationComponent->SetMirror(false);
}

void Client::Object::EnemyType001::OnPostFinalize()
{
	_onEnemy1HitSfx->Stop();
	_onEnemy1HitSfx = nullptr;
}

void Client::Object::EnemyType001::TakeDamage(float Damage)
{
	EnemyBase::TakeDamage(Damage);
	_onEnemy1HitSfx->Play();
	_onEnemy1HitSfx->SetVolume(0.5f);

}
