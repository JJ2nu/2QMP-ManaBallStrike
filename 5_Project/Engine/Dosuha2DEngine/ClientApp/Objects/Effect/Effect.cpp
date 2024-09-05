#include "pch.h"
#include "Effect.h"
#include "Components/EventBindAnimation/EventBindAnimation.h"
#include "Components/Effect/CollsionEffect/CollisionEffect.h"

Client::Object::ImpactEffect::ImpactEffect(Engine::Math::Vector2 _location, Engine::Math::Vector2 _rotation, std::wstring _motion)
{
	location = _location;
	rotation = _rotation;
	motionname = _motion;
}

void Client::Object::ImpactEffect::SetFlashLight()
{
	_light->IsFlash = true;
}

void Client::Object::ImpactEffect::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	_renderOrder = GetBound().bottom;
}

void Client::Object::ImpactEffect::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_effect = CreateComponent<Client::Component::CollisionEffect>
		(L"Resources/Sprites/ManaBall/CollisionEffect/effect_002_012.png", 
			L"Resources/Animation/ManaBall/CollisionEffect/ManaBallHit.csv");
	_effect->SetParentScene(_rootScene);
	_light = CreateComponent<Engine::Component::Spotlight>(_rootScene.lock(), D2D1::ColorF::WhiteSmoke);

}

void Client::Object::ImpactEffect::OnSetup()
{
	_rootScene.lock()->SetLocation(location);
	_boundComponent->SetSize({ 50,50 });
	_effect->IsRenderable = false;
	_effect->SetCollisionPoint(location);
	_effect->SetCollisionDegree(rotation);
		_effect->SetScale({ 0.5f,0.5f });
	_effect->BindMotionBeginEvent(L"Wall", [this]() {

		_effect->IsRenderable = true; 
		});

	
	_effect->BindLastFrameEvent(L"Wall", [this]() {
		Destroy();
		});

	_effect->BindMotionBeginEvent(L"Smash", [this]() {
		_effect->SetScale({ 0.5f,1.f });
		_effect->IsRenderable = true; 
		});
	
	_effect->BindLastFrameEvent(L"Smash", [this]() {
		Destroy();
		});
	

	_effect->BindMotionBeginEvent(L"Enemy", [this]() {
		_effect->SetScale({ 1.2f,1.2f });
		_effect->IsRenderable = true;
		});

	_effect->BindLastFrameEvent(L"Enemy", [this]() {
		Destroy();
		});


	_effect->SetMotion(motionname);
	  _light->SwitchOn();
}

const Engine::Math::Rect& Client::Object::ImpactEffect::GetBound() const
{
	return _boundComponent->GetBound();
}
//=======================================================================================================================
Client::Object::Tail::Tail(Engine::Math::Vector2 _location, Engine::Math::Vector2 _rotation, std::wstring motion) :location(_location),rotation(_rotation), motionname(motion)
{

}

const Engine::Math::Rect& Client::Object::Tail::GetBound() const
{
	return _boundComponent->GetBound();
}

void Client::Object::Tail::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);
	_effect = CreateComponent<Client::Component::EventBindAnimation>(L"Resources/Sprites/ManaBall/TrailEffect/effect_007.png", L"Resources/Animation/ManaBall/TrailEffect/ManaBallTrail.csv");
	_effect->SetParentScene(_rootScene);
}

void Client::Object::Tail::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	_renderOrder = GetBound().bottom;
}

void Client::Object::Tail::OnSetup()
{
	_rootScene.lock()->SetLocation(location);
	_rootScene.lock()->SetRotation(rotation.AngleByAxisX());
	_boundComponent->SetSize({ 65,65 });
	_effect->IsRenderable = false;
	_effect->SetScale({ 0.2f,0.2f });
	_effect->BindMotionBeginEvent(motionname, [this]() {

		_effect->IsRenderable = true;
		});

	_effect->BindLastFrameEvent(motionname, [this]() {
		Destroy();
		});
	
	_effect->SetMotion(motionname);

}
//=======================================================================================================================

Client::Object::RushIndicator::RushIndicator(Engine::Math::Vector2 _location, Engine::Math::Vector2 _targetlocation, std::wstring _path)
	:location(_location) , targetlocation(_targetlocation),bitmapPath(_path)
{

}
const Engine::Math::Rect& Client::Object::RushIndicator::GetBound() const
{
	return _boundComponent->GetBound();

}
void Client::Object::RushIndicator::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);

	_rushIndicatorBitmap = CreateComponent<Engine::Component::FadeBitmap>(bitmapPath);
	_rushIndicatorBitmap->SetParentScene(_rootScene);

}
void Client::Object::RushIndicator::OnSetup()
{
	_renderOrder = -200000;
	_boundComponent->SetSize({ 100,100 });
	_boundComponent->SetLocation(location);
	//_boundComponent->DrawBound();
	bitmapLength = _rushIndicatorBitmap->GetSize().y;
	Engine::Math::Vector2 temp = (targetlocation - location);
	ratio = temp.Magnitude() / bitmapLength;
	degree = temp.AngleByAxisX();
	_rushIndicatorBitmap->SetScale({ 1.f, ratio });
	_rushIndicatorBitmap->SetLocation({ 0, ratio * bitmapLength / 2 });
	_boundComponent->SetRotation(degree);
	_rushIndicatorBitmap->IsRenderable = true;
	_rushIndicatorBitmap->SetDuration(0.3f);
	_rushIndicatorBitmap->BindOnFadeOutEnd([this]()
		{
			Destroy();
		});

}
void Client::Object::RushIndicator::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	rushDelayTimer += deltaGameTime;
	if (rushDelayTimer <= 0.6f)
	{
		_rushIndicatorBitmap->SetScale({ 1.f, ratio });
		_rushIndicatorBitmap->SetLocation({ 0, ratio * bitmapLength / 2 });
		_boundComponent->SetRotation(degree);

	}
	else
	{
		_rushIndicatorBitmap->FadeOut();
	}
}
void Client::Object::RushIndicator::UpdateTargetLocation(Engine::Math::Vector2 _location)
{
	targetlocation = _location;
	Engine::Math::Vector2 temp = (targetlocation - location);
	ratio = temp.Magnitude() / bitmapLength;
	degree = temp.AngleByAxisX()*Engine::Math::Helper::RadianToDegree-90.f;

}
