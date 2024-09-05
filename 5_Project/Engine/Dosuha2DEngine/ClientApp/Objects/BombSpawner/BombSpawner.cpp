#include "pch.h"
#include "BombSpawner.h"
#include "Objects/Bombs/Bombs.h"

Client::Object::BombSpawner::BombSpawner()
	: _spawnTime(0.f), _spawnInterval(0.f)
{

}

const Engine::Math::Rect& Client::Object::BombSpawner::GetBound() const
{
	return _boundComponent->GetBound();
}

void Client::Object::BombSpawner::OnCreateComponent()
{
	_boundComponent = CreateComponent<Engine::Component::Bound>();
	SetRootScene(_boundComponent);
}

void Client::Object::BombSpawner::OnSetup()
{

}

void Client::Object::BombSpawner::OnPostUpdate(float deltaMetaTime, float deltaGameTime)
{

}
