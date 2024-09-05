#include "pch.h"
#include "EnemyExplosion.h"
#include "Objects/Player/ControlPlayer.h"

Client::Object::EnemyExplosion::EnemyExplosion(const Engine::Math::Vector2& location)
	: _location(location), _destroyDelay(0)
{
	const auto enemySection = Manager::Config::GetSection(L"Enemy");
	_explosionRange = enemySection->GetFloat(L"EnemyExplosionRange");
	_explodeDamage = enemySection->GetFloat(L"Enemy1Attack");

	AddTag(L"EnemyAttack", _explodeDamage);
}

const Engine::Math::Rect& Client::Object::EnemyExplosion::GetBound() const
{
	return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::EnemyExplosion::GetColliders() const
{
	return { _circleCollider };
}

void Client::Object::EnemyExplosion::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_circleCollider = CreateComponent<Engine::Component::Collider::Circle>(
		Engine::Component::Collider::Base::Type::Block);
	_circleCollider->SetParentScene(_rootScene);

	_enemyExplosionSfx = Engine::Manager::Audio::GetInstance()->CreateSound(L"Resources/Sounds/sfx_005_1.wav", Audio::ChannelGroupType::Effect, false);
}

void Client::Object::EnemyExplosion::OnSetup()
{
	_rootScene.lock()->SetLocation(_location);
	_circleCollider->SetRadius(_explosionRange / 2.2f);
	_circleCollider->DrawCollider(false);
	_circleCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold& manifold)
		{
			if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Player"))
			{
				const auto playerObject = std::static_pointer_cast<Object::ControlPlayer>(otherObject);
				playerObject->OnHit(_explodeDamage, -manifold.collisionNormal);
			}
		});
	_enemyExplosionSfx->Play();
	_enemyExplosionSfx->SetVolume(1.f);
}

void Client::Object::EnemyExplosion::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	_destroyDelay += deltaGameTime;
	if (_circleCollider->IsActivated() && _destroyDelay >= 0.4f)
	{
		_circleCollider->Deactivate();
		//_circleCollider->DrawCollider(false);
	}
	if (_destroyDelay >= 0.7f)
	{
		Destroy();
		Release();
	}
}

void Client::Object::EnemyExplosion::OnPostFinalize()
{
	_enemyExplosionSfx->Stop();
	_enemyExplosionSfx = nullptr;
}
