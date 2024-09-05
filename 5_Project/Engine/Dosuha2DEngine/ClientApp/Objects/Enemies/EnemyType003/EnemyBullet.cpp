#include "pch.h"
#include "EnemyBullet.h"
#include "Objects/Player/ControlPlayer.h"

Client::Object::EnemyBullet::EnemyBullet(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction)
	: _location(location), _direction(direction)
{
	const auto enemySection = Manager::Config::GetSection(L"Enemy");
	_moveSpeed = enemySection->GetFloat(L"Enemy3AttackSpeed", 220.f);
	_attackPower = enemySection->GetFloat(L"Enemy3Attack", 20.f);

	AddTag(L"EnemyAttack", _attackPower);
}

const Engine::Math::Rect& Client::Object::EnemyBullet::GetBound() const
{
	return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::EnemyBullet::GetColliders() const
{
	return { _circleCollider };
}

void Client::Object::EnemyBullet::OnPostUpdate(float delatMetatTime, float deltaGameTime)
{
	_renderOrder = GetBound().bottom;
}

void Client::Object::EnemyBullet::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_circleCollider = CreateComponent<Engine::Component::Collider::Circle>(
		Engine::Component::Collider::Base::Type::Block);
	_circleCollider->SetParentScene(_rootScene);

	_movementComponent = CreateComponent<Engine::Component::Movement>(_rootScene.lock());

	_animationComponent = CreateComponent<Engine::Component::Animation>(L"Resources/Sprites/Enemy/mon_003_4.png", L"Resources/Animation/Enemy/mon_003_b.csv");
	_animationComponent->SetParentScene(_rootScene);
	_animationComponent->SetScale({ 0.5f, 0.5f });

	_bulletShadow = CreateComponent<Engine::Component::Bitmap>(L"Resources/Sprites/Enemy/effect_016.png");
	_bulletShadow->SetParentScene(_rootScene);
}

void Client::Object::EnemyBullet::OnSetup()
{
	_rootScene.lock()->SetLocation(_location);
	//_boundComponent->DrawBound();
	_boundComponent->SetSize({75,75});
	_movementComponent->SetDirection(_direction);
	_movementComponent->SetSpeed(_moveSpeed);
	_animationComponent->SetMotion(L"Shoot");
	_circleCollider->SetLocation(_circleCollider->GetLocation() + Engine::Math::Vector2(0, 20));
	_circleCollider->SetRadius(15.f);
	_circleCollider->DrawCollider(false);
	_circleCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold& manifold)
		{
			if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Player"))
			{
				const auto playerObject = std::static_pointer_cast<Object::ControlPlayer>(otherObject);
				playerObject->OnHit(_attackPower, -manifold.collisionNormal);
				Destroy();
				Release();
			}
			if (other.lock()->GetOwner().lock()->FindTag(L"Wall"))
			{
				Destroy();
				Release();
			}
		});
	_bulletShadow->SetScale({ 0.3f, 0.3f });
	_bulletShadow->SetLocation(_bulletShadow->GetLocation() + Engine::Math::Vector2(0, 40));
}
