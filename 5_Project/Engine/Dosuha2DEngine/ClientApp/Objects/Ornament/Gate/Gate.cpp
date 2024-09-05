#include "pch.h"
#include "Gate.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"

Client::Object::Gate::Gate(Engine::Math::Vector2 location) : _location(location)
{
	AddTag(L"Wall");
	AddTag(L"Bouncing");
}

void Client::Object::Gate::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	//_doorOverlap = CreateComponent<Engine::Component::Bitmap>(L"Resources/Sprites/door/door_fix.png");
	//_doorOverlap->SetParentScene(_rootScene);

	_doorAnimation = CreateComponent<Component::EventBindAnimation>
		(L"Resources/Sprites/door/object_004.png", L"Resources/Animation/door/DoorFrame.csv");
	_doorAnimation->SetParentScene(_rootScene);

	_doorCollider = CreateComponent<Engine::Component::Collider::Box>(Engine::Component::Collider::Base::Type::Block);
	_doorCollider->SetParentScene(_rootScene);
	_doorCollider->DrawCollider(false);
	_doorExitCollider = CreateComponent<Engine::Component::Collider::Box>(
		Engine::Component::Collider::Base::Type::Overlap);
	_doorExitCollider->SetParentScene(_rootScene);
	_doorOpenSfx = Engine::Manager::Audio::CreateSound(L"Resources/Sounds/sfx_017_1.wav",
	                                                                  Audio::ChannelGroupType::Effect, false);

	_arrow = CreateComponent<Engine::Component::HidableAnimation>(L"Resources/Sprites/door/icon_005.png",
	                                                              L"Resources/Animation/DoorArrow/DoorArrow.csv");
	_arrow->SetParentScene(_rootScene);
}

const Engine::Math::Rect& Client::Object::Gate::GetBound() const
{
	return _boundComponent->GetBound();
}

std::vector<std::shared_ptr<Engine::Component::Collider::Base>> Client::Object::Gate::GetColliders() const
{
	return {_doorCollider, _doorExitCollider};
}


void Client::Object::Gate::OnSetup()
{
	_rootScene.lock()->SetLocation(_location);
	_boundComponent->SetSize({200, 175});
	_doorAnimation->SetLocation({-5, 10.5});
	_doorAnimation->BindMotionBeginEvent(L"Open", [this]()
	{
		_doorOpenSfx->Play();
		_doorOpenSfx->SetVolume(0.5f);
		_doorCollider->Deactivate();
		_doorExitCollider->Activate();
	});




	_doorAnimation->SetMotion(L"Idle");

	_doorCollider->SetSize({400.f, 50.f});
	_doorCollider->SetLocation({0, -15});

	_doorCollider->SetSize({400.f, 50.f});
	_doorCollider->SetLocation({0, -15});
	_doorCollider->BindOnBeginBlock(
		[this](std::weak_ptr<Engine::Component::Base> other, Engine::Math::Collision::Manifold manifold)
		{
			//OnBlock(other, manifold);
		});

	_doorExitCollider->SetSize({500, 30});
	_doorExitCollider->SetLocation({0, -40});
	_doorExitCollider->Deactivate();
	_doorExitCollider->BindOnBeginOverlap(
		[this](const std::weak_ptr<Engine::Component::Collider::Base>& other,
		       const Engine::Math::Collision::Manifold& manifold)
		{
			if (other.lock()->GetOwner().lock()->FindTag(L"Player"))
			{
				if (_onExit != nullptr) _onExit();
			}
		});

	_arrow->SetMotion(L"Idle");
	_arrow->SetScale({0.1f, 0.1f});
	_arrow->SetLocation({0, 160});

	_doorAnimation->BindLastFrameEvent(L"Open", [this]()
	{
		_arrow->Show();
	});
}

void Client::Object::Gate::OnPostUpdate(float deltaMetaTime, float metaGameTime)
{
	_renderOrder = GetBound().bottom - 10;
}

void Client::Object::Gate::OnPostFinalize()
{
	_doorOpenSfx->Stop();
	_doorOpenSfx = nullptr;
}

void Client::Object::Gate::OpenGate() const
{
	_doorAnimation->SetMotion(L"Open");
}

void Client::Object::Gate::BindOnExit(Event event)
{
	_onExit = std::move(event);
}
