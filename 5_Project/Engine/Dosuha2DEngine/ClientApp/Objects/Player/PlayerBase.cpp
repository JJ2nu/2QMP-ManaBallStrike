#include "pch.h"
#include "PlayerBase.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"
#include "Components/DashMovement/DashMovement.h"

Client::Object::PlayerBase::PlayerBase(const Engine::Math::Rect& cameraLimit, const float initialYLocation)
    : _cameraLimit(cameraLimit), _initialYLocation(initialYLocation)
{
    const auto playerSection = Manager::Config::GetSection(L"Player");
}

const Engine::Math::Rect& Client::Object::PlayerBase::GetBound() const
{
    return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::PlayerBase::GetColliders() const
{
    return {_roundRectCollider};
}

void Client::Object::PlayerBase::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _roundRectCollider = CreateComponent<Engine::Component::Collider::RoundRect>(
        Engine::Component::Collider::Base::Type::Block);
    _roundRectCollider->SetParentScene(_rootScene);

    _playerShadow = CreateComponent<Engine::Component::Bitmap>(L"Resources/Sprites/Enemy/effect_016.png");
    _playerShadow->SetParentScene(_rootScene);

    _movementComponent = CreateComponent<Component::DashMovement>(_rootScene.lock());

    _animationComponent = CreateComponent<Component::EventBindAnimation>(
        L"Resources/Sprites/Player/ch_001.png", L"Resources/Animation/Player/Player.csv");
    _animationComponent->SetParentScene(_rootScene);

    _light = CreateComponent<Engine::Component::Spotlight>(_rootScene.lock(), D2D1::ColorF::WhiteSmoke);

    _cameraComponent = CreateComponent<Engine::Component::Camera>(Engine::Manager::Window::GetSize());
    _cameraComponent->SetParentScene(_rootScene);
    Engine::Manager::Camera::SetActivatedCamera(_cameraComponent);
    Engine::Manager::Render::GetShader()->SetCameraMatrix(Engine::Manager::Camera::GetCameraMatrix());
}

void Client::Object::PlayerBase::OnSetup()
{
    ComponentSetup();
    AnimationSetup();
    DataSetup();
}

void Client::Object::PlayerBase::OnPostFinalize()
{
    Base::OnPostFinalize();
    Engine::Manager::Observer<float>::RemoveRegister(L"Speed", _speedRegister);
    _walkSfx->Stop();
    _walkSfx = nullptr;
}

void Client::Object::PlayerBase::ComponentSetup()
{
    _rootScene.lock()->SetScale({1.f, 1.f});
    _rootScene.lock()->SetLocation({0, _initialYLocation});
    _boundComponent->SetSize({ 100, 100 });
    _roundRectCollider->SetSize({100, 100});
    _roundRectCollider->SetRadius(25.f);
   // _roundRectCollider->DrawCollider();
    _animationComponent->SetLocation({ 0,10 });
    _animationComponent->SetMotion(L"Idle");
    _light->SwitchOn();
    _cameraComponent->SetLimit(_cameraLimit);
    _movementComponent->SetSpeed(Manager::Data::GetSpeed());
    _walkSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_002.wav", Audio::ChannelGroupType::Effect,
                                                   true);
    _playerShadow->SetScale({ 0.6f, 0.6f });
    _playerShadow->SetLocation(_playerShadow->GetLocation() + Engine::Math::Vector2(0, 40));

}

void Client::Object::PlayerBase::AnimationSetup()
{
    _animationComponent->BindMotionBeginEvent(L"Idle", [this]()
    {
        _moveflag = false;
        _walkSfx->Stop();
    });
    _animationComponent->BindLastFrameEvent(L"DashUp", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"DashSide", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"DashDownSide", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"DashUpSide", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"DashDown", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"AttackUp", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"AttackDown", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"AttackSide", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
    _animationComponent->BindLastFrameEvent(L"Hit", [this]()
    {
        _animationComponent->SetMotion(L"Idle");
        _moveflag = false;
    });
}

void Client::Object::PlayerBase::DataSetup()
{
    _speedRegister = Engine::Manager::Observer<float>::Register(L"Speed", [this](const float value)
    {
        _movementComponent->SetSpeed(value);
    });
}

void Client::Object::PlayerBase::Move(const Engine::Math::Vector2& direction)
{
    _movementComponent->SetDirection(direction);
    if (!_moveflag)
    {
        _walkSfx->Play();
        _walkSfx->SetVolume(0.5f);
        _animationComponent->SetMotion(L"MoveSide");
        _moveflag = true;
    }
    if (_movementComponent->GetDirection().x > 0) _animationComponent->SetMirror(true);
    else if (_movementComponent->GetDirection().x < 0)_animationComponent->SetMirror(false);
}

void Client::Object::PlayerBase::Stop()
{
    _movementComponent->SetDirection(Engine::Math::Vector2::Zero());
    _animationComponent->SetMotion(L"Idle");
}
