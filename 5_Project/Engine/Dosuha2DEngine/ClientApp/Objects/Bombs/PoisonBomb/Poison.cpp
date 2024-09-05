#include "pch.h"
#include "Poison.h"
#include "Objects/Player/ControlPlayer.h"

Client::Object::Poison::Poison(const Engine::Math::Vector2& location)
	: _location(location), _elapsedTime(0), _reactivateTime(0), _enemyCheckReactivateTime(0)
{
	const auto gimicSection = Manager::Config::GetSection(L"Gimic");
	_toxicRange = gimicSection->GetFloat(L"ToxicRange");
	_toxicTime = gimicSection->GetFloat(L"ToxicTime");
	_toxic = gimicSection->GetFloat(L"ToxicAttack");
}

const Engine::Math::Rect& Client::Object::Poison::GetBound() const
{
	return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::Poison::GetColliders() const
{
	return { _circleCollider };
}

void Client::Object::Poison::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_circleCollider = CreateComponent<Engine::Component::Collider::Circle>(
		Engine::Component::Collider::Base::Type::Block);
	_circleCollider->SetParentScene(_rootScene);

	_enemyCheckCircleCollider = CreateComponent<Engine::Component::Collider::Circle>(
		Engine::Component::Collider::Base::Type::Block);
	_enemyCheckCircleCollider->SetParentScene(_rootScene);

	_animationComponent = CreateComponent<Engine::Component::Animation>(
		L"Resources/Sprites/Object/Bomb/effect_003_3.png", L"Resources/Animation/Object/Bomb/effect_003_2.csv");
	_animationComponent->SetParentScene(_rootScene);
}

void Client::Object::Poison::OnSetup()
{
	_rootScene.lock()->SetLocation(_location);
	_circleCollider->SetRadius(_toxicRange / 2.f);
	_enemyCheckCircleCollider->SetRadius(_toxicRange / 2.f);
	//_circleCollider->DrawCollider(true);
	//_enemyCheckCircleCollider->DrawCollider(true);
	_circleCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold& manifold)
		{
			if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Player"))
			{
				const auto playerObject = std::static_pointer_cast<Object::ControlPlayer>(otherObject);
				playerObject->OnHit(_toxic, -manifold.collisionNormal);
				_circleCollider->Deactivate();
				_reactivateTime = 0.f;
			}
		});
	_enemyCheckCircleCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold& manifold)
		{
			if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"enemy"))
			{
				const auto enemyObject = std::static_pointer_cast<Object::ControlPlayer>(otherObject);
				enemyObject->OnHit(_toxic, -manifold.collisionNormal);
				_enemyCheckCircleCollider->Deactivate();
				_enemyCheckReactivateTime = 0.f;
			}
		});
	_circleCollider->Activate();
	_enemyCheckCircleCollider->Activate();
	_animationComponent->SetScale(Engine::Math::Vector2{ _toxicRange, _toxicRange } / 400.f);
	_animationComponent->SetMotion(L"Explode");
}

void Client::Object::Poison::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	_elapsedTime += deltaGameTime;
	_reactivateTime += deltaGameTime;
	_enemyCheckReactivateTime += deltaGameTime;
	if (_reactivateTime >= 1.0f) _circleCollider->Activate();
	if (_enemyCheckReactivateTime >= 1.0f) _enemyCheckCircleCollider->Activate();
	if (_elapsedTime >= _toxicTime)
	{
		Destroy();
		Release();
	}
}


