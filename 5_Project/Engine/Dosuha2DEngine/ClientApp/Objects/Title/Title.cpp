#include "pch.h"
#include "Title.h"
#include "../../Components/EventBindAnimation/EventBindAnimation.h"


Client::Object::Title::Title()
    : _level(0)
{
    AddTag(L"Bouncing");
    AddTag(L"Wall");
}

const Engine::Math::Rect& Client::Object::Title::GetBound() const
{
    return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::Title::GetColliders() const
{
    return {_boxCollider};
}

void Client::Object::Title::BindOnDamaged(Event event)
{
    _onDamaged = std::move(event);
}

void Client::Object::Title::OnCreateComponent()
{
    _boundComponent = CreateComponent<Engine::Component::Bound>();
    SetRootScene(_boundComponent);

    _bitmapComponent = CreateComponent<Engine::Component::FadeBitmap>(L"Resources/Sprites/Logo/logo_001.png");
    _bitmapComponent->SetParentScene(_rootScene);

    _animation = CreateComponent<Component::EventBindAnimation>(L"Resources/Sprites/Logo/logo_002.png",
                                                                L"Resources/Animation/Logo/Logo.csv");
    _animation->SetParentScene(_rootScene);

    _boxCollider = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Block);
    _boxCollider->SetParentScene(_rootScene);
}

void Client::Object::Title::OnSetup()
{
    _rootScene.lock()->SetScale({0.3f, 0.3f});
    _rootScene.lock()->SetLocation({0, -100});
    _boundComponent->SetSize(_bitmapComponent->GetSize() * 0.8f);
    _boxCollider->SetSize(_bitmapComponent->GetSize() * 0.95f);
    _animation->SetMotion(L"Level0");

    _boxCollider->BindOnBeginBlock(
        [this](const std::weak_ptr<Engine::Component::Collider::Base>& other, Engine::Math::Collision::Manifold)
        {
            if (other.lock()->GetOwner().lock()->FindTag(L"Ball"))
            {
                if (_bitmapComponent->GetOpacity() > 0.f) _bitmapComponent->SetOpacity(0.f);
                if (_level < 3) _animation->SetMotion(L"Level" + std::to_wstring(++_level));
            }
        });

    _animation->BindLastFrameEvent(L"Level3", [this]
    {
        Destroy();
        Release();
        if (_onDamaged != nullptr) _onDamaged();
    });
}
