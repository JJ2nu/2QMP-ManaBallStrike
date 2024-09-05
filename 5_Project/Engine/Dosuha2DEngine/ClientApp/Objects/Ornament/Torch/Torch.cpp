#include "pch.h"
#include "Torch.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"


Client::Object::Torch::Torch(Engine::Math::Vector2 _location) : location(_location)
{
}

Client::Object::Torch::Torch(Engine::Math::Vector2 _location, bool light) : location(_location), islight(light)
{
}

void Client::Object::Torch::OnCreateComponent()
{

	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_torchAnimation = CreateComponent<Client::Component::EventBindAnimation>
		(L"Resources/Sprites/Object/Torch/object_0111.png", L"Resources/Animation/Object/Torch/Torch.csv");
	_torchAnimation->SetParentScene(_rootScene);

	if (islight)_torchLight = CreateComponent<Engine::Component::Spotlight>(_rootScene.lock(), D2D1::ColorF::Orange);

}

void Client::Object::Torch::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	_renderOrder = GetBound().bottom;

}

void Client::Object::Torch::OnSetup()
{
	_rootScene.lock()->SetScale({ 0.7f,0.7f });
	_rootScene.lock()->SetLocation(location);
	_boundComponent->SetSize({ 200,200 });
	_torchAnimation->SetMotion(L"Idle");
	if (islight)_torchLight->SwitchOn();
}

const Engine::Math::Rect& Client::Object::Torch::GetBound() const
{
	return _boundComponent->GetBound();
}
