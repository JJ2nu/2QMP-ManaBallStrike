#include "pch.h"
#include "EndingCreditScroller.h"
#include "../../Components/EventBindAnimation/EventBindAnimation.h"

Client::Object::EndingCreditScroller::EndingCreditScroller()
{
}

const Engine::Math::Rect& Client::Object::EndingCreditScroller::GetBound() const
{
	return _boundComponent->GetBound();
}

void Client::Object::EndingCreditScroller::OnPostUpdate(float d1, float d2)
{

	if (_rootScene.lock()->GetLocation().y <= -2000) _movement->SetSpeed(0);
}

void Client::Object::EndingCreditScroller::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_animation = CreateComponent<Component::EventBindAnimation>(L"Resources/Sprites/CutScene/scene_025.png", L"Resources/Sprites/CutScene/EndingCredit.csv");
	_animation->SetParentScene(_boundComponent);

	_movement = CreateComponent<Engine::Component::Movement>(_rootScene.lock());
}

void Client::Object::EndingCreditScroller::OnSetup()
{
	_rootScene.lock()->SetScale({0.5f,0.5f});
	_rootScene.lock()->SetLocation({300,1000});
	_boundComponent->SetSize({ 1920,2726 });
	_movement->SetDirection({ 0,-1 });
	_movement->SetSpeed(50.f);
}

