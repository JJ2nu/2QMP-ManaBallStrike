#include "pch.h"
#include "RigidbodyComponent.h"

Engine::Component::RigidBody::RigidBody(const std::weak_ptr<Engine::Scene>& rootScene, const float mass, const float restitution)
	: _rootScene(rootScene), _mass(mass), _restitution(restitution),
	_velocity(0, 0), _maxVelocityValue(5000, 5000), _activeGravity(false),
	_gravityScale(9.8f)
{

}

void Engine::Component::RigidBody::Update(float deltaMetaTime, float deltaGameTime)
{
	if (_activeGravity)
	{
		_velocity += Math::Vector2(0, _gravityScale);
	}

	_rootScene->SetLocation(_rootScene->GetLocation() + _velocity * deltaMetaTime);
}

void Engine::Component::RigidBody::AddForce(const Math::Vector2& force)
{
	Math::Vector2 acceleration = force / _mass;
	_velocity += acceleration;

	if (_maxVelocityValue.x < Engine::Math::Helper::Abs()(_velocity.x))
	{
		_velocity.x = _velocity.x / Engine::Math::Helper::Abs()(_velocity.x) * _maxVelocityValue.x;
	}
	if (_maxVelocityValue.y < Engine::Math::Helper::Abs()(_velocity.y))
	{
		_velocity.y = _velocity.y / Engine::Math::Helper::Abs()(_velocity.y) * _maxVelocityValue.y;
	}
}

void Engine::Component::RigidBody::Reflect(const Math::Vector2& normal)
{
	const Math::Vector2 normalvec = normal.Normalize();
	_velocity -= normalvec * 2.f * _velocity.DotProduct(normalvec);
	_velocity *= _restitution;
}

void Engine::Component::RigidBody::SetInitialVelocity(Math::Vector2 initialVelocity)
{
	_velocity = initialVelocity;
}

void Engine::Component::RigidBody::SetGravity(bool isGravity)
{
	_activeGravity = isGravity;
}

void Engine::Component::RigidBody::SetGravityScale(float scale)
{
	_gravityScale = scale;
}

void Engine::Component::RigidBody::SetMass(float mass)
{
	_mass = mass;
}

float Engine::Component::RigidBody::GetMass() const
{
	return _mass;
}

float Engine::Component::RigidBody::GetRestitution() const
{
	return _restitution;
}

const Engine::Math::Vector2& Engine::Component::RigidBody::GetVelocity() const
{
	return _velocity;
}
