#include "pch.h"
#include "Ball.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"
#include "Components/Effect/CollsionEffect/CollisionEffect.h"
#include "Components/Effect/TrailEffect/TrailEffect.h"
#include "../Effect/Effect.h"

Client::Object::Ball::Ball()
    : Ball(Engine::Math::Vector2::Zero(), Engine::Math::Vector2::Zero(), 1.0f, 0.0f, 10, -1)
{
}

Client::Object::Ball::Ball(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction,
                           const float speedRatio, const float damage, const int reflectCount, const size_t id)
    : _id(id), _reflectCount(reflectCount), _setupDirection(direction), _setupLocation(location),
      _speed{}, _setupSpeedRatio(speedRatio), _damage(damage), _isDisappearCancel(false)
{
    AddTag(L"Ball");
    AddTag(L"Damage", _damage);
    const auto ballSection = Manager::Config::GetSection(L"ManaBall");
    _speed = ballSection->GetFloat(L"BallSpeed");
}

const Engine::Math::Rect& Client::Object::Ball::GetBound() const
{
	return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::Ball::GetColliders() const
{
	return { _circleCollider };
}

void Client::Object::Ball::OnPostFinalize()
{

	_ballBounceSfx ->Stop();
	_bookPileSfx ->Stop();
	_chestHitSfx->Stop();
	_ballBounceSfx = nullptr;
	_bookPileSfx = nullptr;
	_chestHitSfx = nullptr;
	Base::OnPostFinalize();
	if (_onDisappear && !_isDisappearCancel) _onDisappear();
}

void Client::Object::Ball::BindOnDisappear(const Event& event)
{
	_onDisappear = event;
}

void Client::Object::Ball::CancelOnDisappear()
{
	_isDisappearCancel = true;
}

size_t Client::Object::Ball::GetId() const
{
    return _id;
}

void Client::Object::Ball::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	_renderOrder = GetBound().bottom;
	if (_isTrailOn)
	{
		_trailEffectElapsedTimer += deltaGameTime;
		if (_trailEffectElapsedTimer >= 0.1f)
		{
			if (_trailEffectIdx == 0)
			{
				const auto tail = _owner.lock()->CreateObject<Client::Object::Tail>(_rootScene.lock()->GetLocation(), _movementComponent->GetDirection(), L"Trail1");
				tail->Initialize(Engine::Manager::Resource::GetLoader());
			}
			else if (_trailEffectIdx == 2)
			{
				const auto tail = _owner.lock()->CreateObject<Client::Object::Tail>(_rootScene.lock()->GetLocation(), _movementComponent->GetDirection(), L"Trail2");
				tail->Initialize(Engine::Manager::Resource::GetLoader());
			}
			else if (_trailEffectIdx == 3)
			{
				const auto tail = _owner.lock()->CreateObject<Client::Object::Tail>(_rootScene.lock()->GetLocation(), _movementComponent->GetDirection(), L"Trail3");
				tail->Initialize(Engine::Manager::Resource::GetLoader());
			}
			else if (_trailEffectIdx == 1)
			{
				const auto tail = _owner.lock()->CreateObject<Client::Object::Tail>(_rootScene.lock()->GetLocation(), _movementComponent->GetDirection(), L"Trail4");
				tail->Initialize(Engine::Manager::Resource::GetLoader());
			}
			_trailEffectIdx = (_trailEffectIdx + 1) % 4;

			_trailEffectElapsedTimer -= 0.1f;
		}
	}
}

void Client::Object::Ball::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

    _manaBall = CreateComponent<Client::Component::EventBindAnimation>(
        L"Resources/Sprites/ManaBall/ManaBall/object_003.png", L"Resources/Animation/ManaBall/ManaBall/ManaBall.csv");
    _manaBall->SetParentScene(_rootScene);

    _manaParticle = CreateComponent<Client::Component::EventBindAnimation>(
        L"Resources/Sprites/ManaBall/ManaBall/effect_009.png",
        L"Resources/Animation/ManaBall/ManaBall/ManaParticle.csv");
    _manaParticle->SetParentScene(_rootScene);

	_circleCollider = CreateComponent<Engine::Component::Collider::Circle>(
		Engine::Component::Collider::Base::Type::Block);
	_circleCollider->SetParentScene(_rootScene);

	_movementComponent = CreateComponent<Engine::Component::Movement>(_rootScene.lock());

	_light = CreateComponent<Engine::Component::Spotlight>(_rootScene.lock(), D2D1::ColorF::WhiteSmoke);
	_ballBounceSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_013.wav",Audio::ChannelGroupType::Effect,false);
	_chestHitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_035.wav", Audio::ChannelGroupType::Effect, false);
	_bookPileSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_036.wav", Audio::ChannelGroupType::Effect, false);
}

void Client::Object::Ball::OnSetup()
{
	_rootScene.lock()->SetScale({ 0.2f, 0.2f });
	_rootScene.lock()->SetLocation(_setupLocation);
	_movementComponent->SetSpeed(_speed * _setupSpeedRatio);
	_movementComponent->SetDirection(_setupDirection);
	_manaBall->SetScale({ 1.5f, 1.5f });
	_manaBall->SetMotion(L"Idle");
	_manaParticle->SetScale({ 1.5f, 1.5f });

	_boundComponent->SetSize({ 200,200});
	_circleCollider->SetRadius(_manaBall->GetSize().x * 0.24f);
	_circleCollider->BindOnBeginBlock(
		[this](const std::weak_ptr<Engine::Component::Collider::Base>& other,
			const Engine::Math::Collision::Manifold& manifold)
		{
			if (other.lock()->GetOwner().lock()->FindTag(L"Bouncing")) Bounce(manifold.collisionNormal);
			if (other.lock()->GetOwner().lock()->FindTag(L"Wall"))
			{
				auto effect = _owner.lock()->CreateObject<Client::Object::ImpactEffect>(manifold.collisionPoint, -manifold.collisionNormal, L"Wall");
				effect->Initialize(Engine::Manager::Resource::GetLoader());
			}
			if (other.lock()->GetOwner().lock()->FindTag(L"Enemy"))
			{
				auto effect = _owner.lock()->CreateObject<Client::Object::ImpactEffect>(manifold.collisionPoint, -manifold.collisionNormal, L"Enemy");
				effect->Initialize(Engine::Manager::Resource::GetLoader());
			}
		});
	_circleCollider->BindOnEndOverlap([this](const std::weak_ptr<Engine::Component::Collider::Base>& other, const Engine::Math::Collision::Manifold&)
	{
		if (other.lock()->GetOwner().lock()->FindTag(L"Background"))
		{
			Destroy();
			Release();
		}
	});
	_manaBall->SetMotion(L"Idle");
	_light->SetProperty(Engine::Component::LightProp::color, D2D1::ColorF::WhiteSmoke);

	_light->SwitchOn();
}

void Client::Object::Ball::Bounce(const Engine::Math::Vector2& normal)
{
	_ballBounceSfx->Play();

	if (normal.DotProduct(_movementComponent->GetDirection()) < 0)
		_movementComponent->SetDirection(
			_movementComponent->GetDirection().Reflect(normal));
	DecreaseReflectCount();
}

void Client::Object::Ball::DecreaseReflectCount()
{
	if (--_reflectCount <= 0)
	{
		Destroy();
		Release();
	}
	if (_reflectCount <= 5)
	{
		_manaBall->SetMotion(L"Red");
		_light->SetProperty(Engine::Component::LightProp::color, D2D1::ColorF::Orange);

	}
	if (_reflectCount <= 2)
	{
		_manaBall->SetMotion(L"Warning");

	}

}

Client::Object::NormalBall::NormalBall(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction,
                                       const size_t id)
    : Ball(location, direction, Manager::Config::GetSection(L"ManaBall")->GetFloat(L"NormalBallSpeedRatio"),
           Manager::Config::GetSection(L"ManaBall")->GetFloat(L"NormaBallDamage"),
           Manager::Config::GetSection(L"ManaBall")->GetInt(L"NormalBallBounceCount") + Manager::Data::GetAdditionalManaBallCount(), id)
{
}

Client::Object::PerfectServeBall::PerfectServeBall(const Engine::Math::Vector2& location,
                                                   const Engine::Math::Vector2& direction, const size_t id)
    : Ball(location, direction, Manager::Config::GetSection(L"ManaBall")->GetFloat(L"PerfectServeBallSpeedRatio"),
           Manager::Config::GetSection(L"ManaBall")->GetFloat(L"PerfectServeBallDamage"),
           Manager::Config::GetSection(L"ManaBall")->GetInt(L"PerfectServeBallBounceCount") + Manager::Data::GetAdditionalManaBallCount(), id)
{
	_isTrailOn = true;
}

Client::Object::HitBall::HitBall(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction,
                                 const size_t id)
    : Ball(location, direction, Manager::Config::GetSection(L"ManaBall")->GetFloat(L"HitBallSpeedRatio"),
           Manager::Config::GetSection(L"ManaBall")->GetFloat(L"HitBallDamage"),
           Manager::Config::GetSection(L"ManaBall")->GetInt(L"HitBallBounceCount") + Manager::Data::GetAdditionalManaBallCount(), id)
{
}


Client::Object::SmashBall::SmashBall(const Engine::Math::Vector2& location, const Engine::Math::Vector2& direction,
                                     const size_t id)
    : Ball(location, direction, Manager::Config::GetSection(L"ManaBall")->GetFloat(L"SmashBallSpeedRatio"),
           Manager::Config::GetSection(L"ManaBall")->GetFloat(L"SmashBallDamage"),
           Manager::Config::GetSection(L"ManaBall")->GetInt(L"SmashBallBounceCount") + Manager::Data::GetAdditionalManaBallCount(), id)
{
	_isTrailOn = true;

}
