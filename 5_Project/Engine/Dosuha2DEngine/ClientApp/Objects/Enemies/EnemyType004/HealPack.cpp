#include "pch.h"
#include "HealPack.h"
#include "Objects/Player/ControlPlayer.h"

Client::Object::HealPack::HealPack(const Engine::Math::Vector2& location)
	: _location(location), _elapsedTime(0), _reactivateTime(0)
{
	const auto gimicSection = Manager::Config::GetSection(L"Gimic");
	_healingRange = gimicSection->GetFloat(L"HealingRange");
	_healingTime = gimicSection->GetFloat(L"HealingTime");
	_heal = gimicSection->GetFloat(L"Healing");
}

const Engine::Math::Rect& Client::Object::HealPack::GetBound() const
{
	return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::HealPack::GetColliders() const
{
	return { _circleCollider };
}

void Client::Object::HealPack::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_circleCollider = CreateComponent<Engine::Component::Collider::Circle>(
		Engine::Component::Collider::Base::Type::Block);
	_circleCollider->SetParentScene(_rootScene);

	_animationComponent = CreateComponent<Engine::Component::Animation>(
		L"Resources/Sprites/Object/Bomb/effect_014.png", L"Resources/Animation/Object/Bomb/effect_014.csv");
	_animationComponent->SetParentScene(_rootScene);
}

void Client::Object::HealPack::OnSetup()
{
	_rootScene.lock()->SetLocation(_location);
	_circleCollider->SetRadius(_healingRange / 2.f);
	_circleCollider->DrawCollider(false);
	_circleCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold& manifold)
		{
			if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Player"))
			{
				const auto playerObject = std::static_pointer_cast<Object::ControlPlayer>(otherObject);
				playerObject->Healing(_heal);
				_circleCollider->Deactivate();
				_reactivateTime = 0.f;
			}
		});
	_circleCollider->Activate();
	_animationComponent->SetScale(Engine::Math::Vector2{ _healingRange, _healingRange } / 400.f);
	_animationComponent->SetMotion(L"Heal");
}

void Client::Object::HealPack::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	_elapsedTime += deltaGameTime;
	_reactivateTime += deltaGameTime;
	if (_reactivateTime >= 1.0f) _circleCollider->Activate();
	if (_elapsedTime >= _healingTime)
	{
		Destroy();
		Release();
	}
}


