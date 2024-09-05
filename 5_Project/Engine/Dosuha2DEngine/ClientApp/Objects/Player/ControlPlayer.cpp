#include "pch.h"
#include "ControlPlayer.h"
#include "Components/TimingBar/TimingBar.h"
#include "Components/Indicator/Indicator.h"
#include "Components/DashMovement/DashMovement.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"
#include "Components/Effect/SwingEffect/SwingEffect.h"
#include "Components/Staff/Staff.h"
#include "../Ball/Ball.h"
#include "../Effect/Effect.h"

Client::Object::ControlPlayer::ControlPlayer(const float initialYLocation)
    : PlayerBase(Engine::Math::Rect{-800, -530, 800, 530}, initialYLocation),
      _weaponRange{}, _ballSpawnOffset(100.f), _superElapsedTime(0.f), _superTime{},
      _isSuper(false), _isDashing(false), _ballDelay{}, _ballSpawnElapsedTime(0.f), _isDelay(false), _isPoisoned(false),
      _ballPool(Manager::Data::GetMaxManaBallCount(),
                Manager::Config::GetSection(L"ManaBall")->GetFloat(L"BallCoolTime")),
      _isSlow(false), _slowRatio(0.01f), _slowDuration(0.15f), _slowElapsedTime(0.0f), _useController(false)
{
    AddTag(L"Player");
    Engine::Math::Helper::GetSinCos()(cos_60, cos_30, 30);
    const auto playerSection = Manager::Config::GetSection(L"Player");
    _weaponRange = playerSection->GetFloat(L"HitRange");
    _superTime = playerSection->GetFloat(L"SuperTime");
    const auto ballSection = Manager::Config::GetSection(L"ManaBall");
    _ballDelay = ballSection->GetFloat(L"BallDelay");
    const auto gimicSection = Manager::Config::GetSection(L"Gimic");
    _posionDamage = gimicSection->GetFloat(L"ToxicAttack");
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::ControlPlayer::GetColliders() const
{
    auto colliders = PlayerBase::GetColliders();
    colliders.push_back(_weapon);
    return colliders;
}

void Client::Object::ControlPlayer::OnCreateComponent()
{
    PlayerBase::OnCreateComponent();
    _indicator = CreateComponent<Component::Indicator>();
    _indicator->SetParentScene(_rootScene);

    _swingAnimation = CreateComponent<Component::SwingEffect>(L"Resources/Sprites/Player/effect_001.png",
                                                              L"Resources/Animation/Player/PlayerSwing.csv");
    _swingAnimation->SetParentScene(_rootScene);

    _timingBar = CreateComponent<Component::TimingBar>();
    _timingBar->SetParentScene(_rootScene);

    _weapon = CreateComponent<Component::Staff>(_weaponRange);
    _weapon->SetParentScene(_indicator);

    _swingSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_001_3.wav", Audio::ChannelGroupType::Effect,
                                                    false);
    _normalHitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_011.wav",
                                                        Audio::ChannelGroupType::Effect, false);
    _smashHitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_012.wav", Audio::ChannelGroupType::Effect,
                                                       false);

    _dashSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_015.wav", Audio::ChannelGroupType::Effect,
                                                   false);

    _onHitSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_019.wav", Audio::ChannelGroupType::Effect,
                                                    false);
    _heartBeatSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_024.wav",
                                                        Audio::ChannelGroupType::Effect, true);
    _onDeathSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_021.wav", Audio::ChannelGroupType::Effect,
                                                      false);

    _ScreenSmashEffect = CreateComponent<Engine::Component::FadeBitmap>(
        L"Resources/Sprites/ManaBall/CollisionEffect/effect_smash.png");
    _ScreenSmashEffect->SetParentScene(_cameraComponent);
}

void Client::Object::ControlPlayer::OnPostFinalize()
{
    PlayerBase::OnPostFinalize();
    _swingSfx->Stop();
    _normalHitSfx->Stop();
    _smashHitSfx->Stop();
    _dashSfx->Stop();
    _onHitSfx->Stop();
    _heartBeatSfx->Stop();
    _onDeathSfx->Stop();
    _swingSfx = nullptr;
    _normalHitSfx = nullptr;
    _smashHitSfx = nullptr;
    _dashSfx = nullptr;
    _onHitSfx = nullptr;
    _heartBeatSfx = nullptr;
    _onDeathSfx = nullptr;
    Engine::Manager::Observer<float>::RemoveRegister(L"HealthPoint", _healthRegister);
}

void Client::Object::ControlPlayer::ReleaseInput()
{
    Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Move")->ClearListener();
    Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"TimingBar")->ClearListener();
    Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Serve")->ClearListener();
    Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Dash")->ClearListener();
    Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Swing")->ClearListener();
    Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"ControllerAim")->ClearListener();
    Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"MouseAim")->ClearListener();
}

void Client::Object::ControlPlayer::OnSetup()
{
    PlayerBase::OnSetup();
    InputSetup();
    SoundSetup();
    _roundRectCollider->BindOnBlock(
        [this](const std::weak_ptr<Engine::Component::Collider::Base>& other,
               const Engine::Math::Collision::Manifold& manifold)
        {
            if (other.lock()->GetOwner().lock()->FindTag(L"Wall"))
            {
                _rootScene.lock()->SetLocation(
                    _rootScene.lock()->GetLocation() + (manifold.collisionNormal * manifold.overlapAmount));
            }
        });
    _ScreenSmashEffect->IsRenderable = false;
    _ScreenSmashEffect->SetOpacity(0.05f);
}

void Client::Object::ControlPlayer::DataSetup()
{
    PlayerBase::DataSetup();
    _healthRegister = Engine::Manager::Observer<float>::Register(L"HealthPoint", [this](const float value)
    {
        if (value <= 0.f)
        {
            Die();
        }
    });
}

void Client::Object::ControlPlayer::ComponentSetup()
{
    PlayerBase::ComponentSetup();
    _swingAnimation->SetMotion(L"Idle");
    _swingAnimation->SetScale({0.9f, 1.5f});
    _swingAnimation->IsRenderable = false;
    _roundRectCollider->BindOnBeginBlock([this](const std::weak_ptr<Engine::Component::Collider::Base>& other,
                                                const Engine::Math::Collision::Manifold& manifold)
    {
        if (const auto otherObject = other.lock()->GetOwner().lock(); otherObject->FindTag(L"Enemy"))
        {
            if (otherObject->GetTag(L"EnemyAttack"))
            {
                const auto damage = otherObject->GetTag(L"EnemyAttack")->GetValue();
                OnHit(*damage, -manifold.collisionNormal);
            }
        }
    });
    _indicator->SetScale({0.6f, 0.6f});
    _weapon->SetLocation({0, -200});
    _weapon->SetScale({4, 4});
    _weapon->BindOnHit([this](const Engine::Math::Vector2& ballLocation, const size_t id)
    {
        OnSwingHit(ballLocation, id);
    });
    _weapon->BindOnSmash([this](const Engine::Math::Vector2& ballLocation, const size_t id)
    {
        OnSwingSmash(ballLocation, id);
    });
    _timingBar->SetLocation({0, -90});
    _timingBar->BindOnPerfect([this]() { OnServeSuccess(); });
    _timingBar->BindOnFail([this]() { OnServeFail(); });
}

void Client::Object::ControlPlayer::InputSetup()
{
    const auto moveAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Move");
    moveAction->AddListener(Input::TriggerState::Triggered, [this](const Input::Value& value) { Move(value); });
    moveAction->AddListener(Input::TriggerState::Completed, [this](const Input::Value& _) { Stop(); });

    const auto timingBarAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"TimingBar");
    timingBarAction->AddListener(Input::TriggerState::Started, [this](const Input::Value& _) { OpenTimingBar(); });
    timingBarAction->AddListener(Input::TriggerState::Completed, [this](const Input::Value& _) { CloseTimingBar(); });

    const auto serveAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Serve");
    serveAction->AddListener(Input::TriggerState::Started, [this](const Input::Value& _) { Serve(); });

    const auto dashAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Dash");
    dashAction->AddListener(Input::TriggerState::Started, [this](const Input::Value& _) { Dash(); });

    const auto swingAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Swing");
    swingAction->AddListener(Input::TriggerState::Started, [this](const Input::Value& _) { Swing(); });

    const auto controllerAimAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(
        L"ControllerAim");
    controllerAimAction->AddListener(Input::TriggerState::Triggered, [this](const Input::Value& value) { Aim(value); });
    controllerAimAction->AddListener(Input::TriggerState::Started, [this](const Input::Value& _)
    {
        _useController = true;
    });

    const auto mouseAimAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"MouseAim");
    mouseAimAction->AddListener(Input::TriggerState::Triggered, [this](const Input::Value& value)
    {
        if (!_useController)MouseAim(value);
    });

    const auto switchingAction = Engine::Manager::Input::CreateMappingContext(L"Player")->GetAction(L"Switching");
    switchingAction->AddListener(Input::TriggerState::Started, [this](const Input::Value& _)
    {
        _useController = !_useController;
    });
}

void Client::Object::ControlPlayer::SoundSetup()
{
}

void Client::Object::ControlPlayer::AnimationSetup()
{
    PlayerBase::AnimationSetup();
    _swingAnimation->BindMotionBeginEvent(L"Idle", [this]() { _swingAnimation->IsRenderable = true; });
    _swingAnimation->BindLastFrameEvent(L"Idle", [this]() { _swingAnimation->IsRenderable = false; });
}

void Client::Object::ControlPlayer::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
    _isDashing = _movementComponent->IsDashing();
    _renderOrder = _boundComponent->GetBound().bottom - 5;


    Engine::Math::Vector2 templocation = _rootScene.lock()->GetLocation();
    if (_renderOrder <= -350) _indicator->IsRenderable = false;
    else _indicator->IsRenderable = true;
    if (templocation.y < -425)_rootScene.lock()->SetLocation({templocation.x, -425});
}

void Client::Object::ControlPlayer::OnPreFinalize()
{
    ReleaseInput();
}


void Client::Object::ControlPlayer::Dash() const
{
    if (_movementComponent->GetDirection() != Engine::Math::Vector2::Zero() && _movementComponent->Dash())
    {
        _dashSfx->Play();
        Engine::Math::Vector2 playerDirection = _movementComponent->GetDirection();
        if (playerDirection.DotProduct(Engine::Math::Vector2::Right()) > cos_30
            || playerDirection.DotProduct(Engine::Math::Vector2::Left()) > cos_30)
            _animationComponent->SetMotion(L"DashSide");
        else if (playerDirection.DotProduct(Engine::Math::Vector2::Up()) > cos_30)
            _animationComponent->SetMotion(L"DashUp");
        else if (playerDirection.DotProduct(Engine::Math::Vector2::Down()) > cos_30)
            _animationComponent->SetMotion(L"DashDown");
        else if (playerDirection.DotProduct(Engine::Math::Vector2::Up()) <= cos_30
            && playerDirection.DotProduct(Engine::Math::Vector2::Up()) >= cos_60)
            _animationComponent->SetMotion(L"DashUpSide");
        else if (playerDirection.DotProduct(Engine::Math::Vector2::Down()) <= cos_30
            && playerDirection.DotProduct(Engine::Math::Vector2::Down()) >= cos_60)
            _animationComponent->SetMotion(L"DashDownSide");
    }
}

void Client::Object::ControlPlayer::Die()
{
    _onDeathSfx->Play();
    _animationComponent->SetMotion(L"Death");
    _movementComponent->SetDirection(Engine::Math::Vector2::Zero());
    ReleaseInput();
    _isDead = true;
    if (_onDeath != nullptr) { _onDeath(); }
}

void Client::Object::ControlPlayer::OpenTimingBar() const
{
    if (!_ballPool.AnyAlive() || _isDelay) return;
    _timingBar->Show();
    _timingBar->Start();
}

void Client::Object::ControlPlayer::CloseTimingBar() const
{
    _timingBar->Hide();
    _timingBar->Reset();
}

void Client::Object::ControlPlayer::Serve() const
{
    if (_timingBar->IsMakerMove()) _timingBar->Stop();
}

void Client::Object::ControlPlayer::Swing() const
{
    _swingSfx->Play();
    _swingSfx->SetVolume(0.3f);
    if (!_timingBar->IsShow()) _weapon->Swing();
    _swingAnimation->SetMotion(L"Idle");

    //set motion&mirror along the degree
    float degree = _swingAnimation->GetDegree();
    if (degree >= 225 || degree < -45)
    {
        _swingAnimation->SetMirror(true);
        _animationComponent->SetMotion(L"AttackSide");
        _animationComponent->SetMirror(false);
    }
    else if (degree >= -45 && degree < 0)
    {
        _swingAnimation->SetMirror(false);
        _animationComponent->SetMotion(L"AttackUp");
        _animationComponent->SetMirror(true);
    }
    else if (degree >= 0 && degree < 45)
    {
        _swingAnimation->SetMirror(true);
        _animationComponent->SetMotion(L"AttackUp");
        _animationComponent->SetMirror(false);
    }
    else if (degree >= 45 && degree < 135)
    {
        _swingAnimation->SetMirror(false);
        _animationComponent->SetMotion(L"AttackSide");
        _animationComponent->SetMirror(true);
    }
    else if (degree >= 135 && degree < 180)
    {
        _swingAnimation->SetMirror(false);
        _animationComponent->SetMotion(L"AttackDown");
        _animationComponent->SetMirror(false);
    }
    else if (degree >= 180 && degree < 225)
    {
        _swingAnimation->SetMirror(true);
        _animationComponent->SetMotion(L"AttackDown");
        _animationComponent->SetMirror(true);
    }
}

void Client::Object::ControlPlayer::OnHit(const float damage, const Engine::Math::Vector2& direction)
{
    if (_isSuper || _isDashing) return;
    _onHitSfx->Play();
    _movementComponent->KnockBack(direction);
    if (Manager::Data::GetHealthPoint() <= 20)
    {
        if (!_heartBeatSfx->IsPlaying())
        {
            _heartBeatSfx->Play();
            _heartBeatSfx->SetVolume(0.3f);
        }
    }
    _animationComponent->SetMotion(L"Hit");
    _isSuper = true;
    Manager::Data::SetHealthPoint(Manager::Data::GetHealthPoint() - damage);
}

void Client::Object::ControlPlayer::Healing(const float healing) const
{
    Manager::Data::SetHealthPoint(
        Engine::Math::Helper::Min()(Manager::Data::GetHealthPoint() + healing, Manager::Data::GetMaxHealthPoint()));
    if (Manager::Data::GetHealthPoint() > 20) _heartBeatSfx->Stop();
}

void Client::Object::ControlPlayer::BindOnDeath(Event event)
{
    _onDeath = std::move(event);
}

void Client::Object::ControlPlayer::OnServeSuccess()
{
    // Perfect serve ball
    _smashHitSfx->Play();
    _smashHitSfx->SetVolume(0.5f);
    const size_t index = _ballPool.GetAliveIndex();
    const auto ball = _owner.lock()->CreateObject<PerfectServeBall>(GetServeLocation(), GetBallDirection(), index);
    ball->BindOnDisappear([this, index]() { _ballPool.RestoreOne(index); });
    ball->Initialize(Engine::Manager::Resource::GetLoader());
    ball->Update(Engine::Manager::Time::GetDeltaMetaTime(), Engine::Manager::Time::GetDeltaGameTime());
    _timingBar->Hide();
    _timingBar->Reset();
    _ballPool.UseOne(index);
    _isDelay = true;
}

void Client::Object::ControlPlayer::OnServeFail()
{
    // Normal serve ball
    _normalHitSfx->Play();
    _normalHitSfx->SetVolume(0.5f);
    const size_t index = _ballPool.GetAliveIndex();
    const auto ball = _owner.lock()->CreateObject<NormalBall>(GetServeLocation(), GetBallDirection(), index);
    ball->BindOnDisappear([this, index]() { _ballPool.RestoreOne(index); });
    ball->Initialize(Engine::Manager::Resource::GetLoader());
    ball->Update(Engine::Manager::Time::GetDeltaMetaTime(), Engine::Manager::Time::GetDeltaGameTime());
    _timingBar->Hide();
    _timingBar->Reset();
    _ballPool.UseOne(index);
    _isDelay = true;
}

void Client::Object::ControlPlayer::OnSwingHit(Engine::Math::Vector2 ballLocation, const size_t id)
{
    // Swing hit ball
    _normalHitSfx->Play();
    _normalHitSfx->SetVolume(0.5f);
    const auto ball = _owner.lock()->CreateObject<HitBall>(ballLocation, GetBallDirection(), id);
    ball->BindOnDisappear([this, id]() { _ballPool.RestoreOne(id); });
    ball->Initialize(Engine::Manager::Resource::GetLoader());
    ball->Update(Engine::Manager::Time::GetDeltaMetaTime(), Engine::Manager::Time::GetDeltaGameTime());
    const auto effect = _owner.lock()->CreateObject<Client::Object::ImpactEffect>(
        ball->GetLocation(), -GetBallDirection(), L"Smash");
    effect->Initialize(Engine::Manager::Resource::GetLoader());
}

void Client::Object::ControlPlayer::OnSwingSmash(Engine::Math::Vector2 ballLocation, const size_t id)
{
    _smashHitSfx->Play();
    _smashHitSfx->SetVolume(0.5f);

    const auto ball = _owner.lock()->CreateObject<SmashBall>(ballLocation, GetBallDirection(), id);
    ball->BindOnDisappear([this, id]() { _ballPool.RestoreOne(id); });
    ball->Initialize(Engine::Manager::Resource::GetLoader());
    ball->Update(Engine::Manager::Time::GetDeltaMetaTime(), Engine::Manager::Time::GetDeltaGameTime());
    const auto effect = _owner.lock()->CreateObject<Client::Object::ImpactEffect>(
        ball->GetLocation(), -GetBallDirection(), L"Smash");
    effect->Initialize(Engine::Manager::Resource::GetLoader());
    effect->SetFlashLight();
    Slow();
}

void Client::Object::ControlPlayer::Slow()
{
    Engine::Manager::Time::SetTimeScale(_slowRatio);
    _ScreenSmashEffect->IsRenderable = true;
    Engine::Manager::Input::GetController().StartVibration(
        Manager::Config::GetSection(L"Input")->GetFloat(L"ControllerVibrationIntensity"));
    _isSlow = true;
}

void Client::Object::ControlPlayer::Aim(const Engine::Math::Vector2& direction) const
{
    _indicator->SetDirection(direction);
    _swingAnimation->SetDirection(direction);
}

void Client::Object::ControlPlayer::MouseAim(const Engine::Math::Vector2& mousePosition) const
{
    const Engine::Math::Vector2 playerLocation = _rootScene.lock()->GetLocation();
    D2D1::Matrix3x2F cameraMatrix = Engine::Manager::Camera::GetCameraMatrix();
    cameraMatrix.Invert();
    Aim((Engine::Math::Vector2{cameraMatrix.TransformPoint(mousePosition)} - playerLocation).Normalize());
}

Engine::Math::Vector2 Client::Object::ControlPlayer::GetServeLocation() const
{
    return _rootScene.lock()->GetLocation() + GetBallDirection() * _ballSpawnOffset;
}

Engine::Math::Vector2 Client::Object::ControlPlayer::GetBallDirection() const
{
    return _indicator->GetDirection();
}

void Client::Object::ControlPlayer::OnPreUpdate(const float deltaMetaTime, const float deltaGameTime)
{
    Base::OnPreUpdate(deltaMetaTime, deltaGameTime);
    UpdateSuper(deltaGameTime);
    UpdateDelay(deltaGameTime);
    UpdateSlow(deltaMetaTime);
    _ballPool.Update(deltaGameTime);
    Manager::Data::SetManaBallCount(_ballPool.GetAliveCount());
}

void Client::Object::ControlPlayer::UpdateSuper(const float deltaGameTime)
{
    if (!_isSuper) return;
    _superElapsedTime += deltaGameTime;
    if (_superElapsedTime < _superTime) return;
    _isSuper = false;
    _superElapsedTime = 0.f;
}

void Client::Object::ControlPlayer::UpdateDelay(const float deltaGameTime)
{
    if (!_isDelay) return;
    _ballSpawnElapsedTime += deltaGameTime;
    if (_ballSpawnElapsedTime < _ballDelay) return;
    _isDelay = false;
    _ballSpawnElapsedTime = 0.f;
}

void Client::Object::ControlPlayer::UpdateSlow(const float deltaMetaTime)
{
    if (!_isSlow) return;
    _slowElapsedTime += deltaMetaTime;
    if (_slowElapsedTime < _slowDuration) return;
    Engine::Manager::Time::SetTimeScale(1.0f);
    Engine::Manager::Input::GetController().StopVibration();
    _isSlow = false;
    _ScreenSmashEffect->IsRenderable = false;
    _slowElapsedTime = 0.f;
}
