#include "pch.h"
#include "RigidbodyTestObject.h"

const Engine::Math::Rect& Client::Object::RigidbodyTestObject::GetBound() const
{
	return _boundComponent->GetBound();
}

void Client::Object::RigidbodyTestObject::OnCreateComponent()
{
	_boxComponent = CreateComponent<Engine::Component::Shape::Box>(Engine::Math::Vector2{50, 50},
	                                                               D2D1::ColorF(D2D1::ColorF::Red));
	_boxComponent->SetLocation({-900, -300});
	SetRootScene(_boxComponent);

	_boundComponent = CreateComponent<Engine::Component::Bound>(Engine::Math::Vector2{1, 1});
	_boundComponent->SetParentScene(_rootScene);

	_rigidbodyComponent = CreateComponent<Engine::Component::RigidBody>(_rootScene.lock(), 1.0f, 0.8f);
	_rigidbodyComponent->SetGravity();
	_rigidbodyComponent->SetGravityScale(3.f);
	_rigidbodyComponent->SetInitialVelocity({0, -300});
	_rigidbodyComponent->AddForce({100, 0});
}

void Client::Object::RigidbodyTestObject::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{
	Engine::Math::Vector2 position = _rootScene.lock()->GetLocation();

	if (position.y > 500)
	{
		_rigidbodyComponent->Reflect({0, -1});
		_rootScene.lock()->SetLocation({position.x, 500.f - 0.1f});
	}
}
