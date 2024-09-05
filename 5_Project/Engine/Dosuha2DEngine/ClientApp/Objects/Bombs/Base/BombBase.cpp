#include "pch.h"
#include "BombBase.h"

Client::Object::BombBase::BombBase(const Engine::Math::Vector2& location)
    : _location(location), _elapsedTime(0), _explosionInterval(1.5f), _willExplode(false), _isExploded(false), _explosionEffect(false)
{
    AddTag(L"Bomb");
}

const Engine::Math::Rect& Client::Object::BombBase::GetBound() const
{
    return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::BombBase::GetColliders() const
{
    return { _circleCollider, _explodeCollider };
}

void Client::Object::BombBase::Explosion()
{
    _willExplode = true;
}

void Client::Object::BombBase::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _circleCollider = CreateComponent<Engine::Component::Collider::Circle>(
        Engine::Component::Collider::Base::Type::Overlap);
    _circleCollider->SetParentScene(_rootScene);

    _explodeCollider = CreateComponent<Engine::Component::Collider::Circle>(
        Engine::Component::Collider::Base::Type::Block);
    _explodeCollider->SetParentScene(_rootScene);

    _bombShadow = CreateComponent<Engine::Component::Bitmap>(L"Resources/Sprites/Enemy/effect_016.png");
    _bombShadow->SetParentScene(_rootScene);

    _onExplosionSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_029.mp3", Audio::ChannelGroupType::Effect, false);
}

void Client::Object::BombBase::OnSetup()
{
    _rootScene.lock()->SetLocation(_location);
    _boundComponent->SetSize({75,75});
    _circleCollider->SetRadius(35.f);
    _circleCollider->SetLocation(_circleCollider->GetLocation() + Engine::Math::Vector2(5, 0));
    _explodeCollider->SetRadius(300.f);
    _explodeCollider->Deactivate();
    _animationComponent->SetMotion(L"Idle");
    _bombShadow->SetScale({ 0.5f, 0.5f });
    _bombShadow->SetLocation(_bombShadow->GetLocation() + Engine::Math::Vector2(5, 25));
}

void Client::Object::BombBase::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    _renderOrder = GetBound().bottom;
    UpdateBomb(deltaGameTime);
}

void Client::Object::BombBase::OnPostFinalize()
{
    _onExplosionSfx->Stop();
    _onExplosionSfx = nullptr;
}

void Client::Object::BombBase::UpdateBomb(float deltaGameTime)
{
    if (_isExploded)
    {
        if (!_explosionEffect)
        {
            ExplosionEffect();
            _explosionEffect = true;
        }

        _elapsedTime += deltaGameTime;
        if (_elapsedTime >= 0.7f)
        {
            Destroy();
            Release();
        }
        return;
    }

    if (_willExplode)
    {
        if (_elapsedTime == 0) _animationComponent->SetMotion(L"Explode");

        _elapsedTime += deltaGameTime;
        if (_elapsedTime >= _explosionInterval)
        {
            _explodeCollider->Activate();
            _willExplode = false;
            _isExploded = true;
            _elapsedTime = 0;
        }
    }
}

void Client::Object::BombBase::ExplosionEffect()
{
    _effectAnimation->SetMotion(L"Explode");
    _animationComponent->SetMotion(L"Effect");
    _onExplosionSfx->Play();
    _onExplosionSfx->SetVolume(1.0f);
}

