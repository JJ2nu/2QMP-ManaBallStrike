#include "pch.h"
#include "Circle.h"

Engine::Math::Circle Engine::Math::Circle::Zero()
{
	return {Vector2::Zero(), 0};
}

Engine::Math::Circle Engine::Math::Circle::UnitCircle()
{
	return {{0, 0}, 1};
}

Engine::Math::Circle::Circle()
	: center{0, 0}, radius(0)
{
}

Engine::Math::Circle::Circle(const float radius)
	: center{0, 0}, radius(radius)
{
}

Engine::Math::Circle::Circle(const float x, const float y, const float radius)
	: center{x, y}, radius(radius)
{
}

Engine::Math::Circle::Circle(const Vector2& center, const float radius)
	: center(center), radius(radius)
{
}

Engine::Math::Circle::operator D2D1_ELLIPSE() const
{
	return D2D1::Ellipse(center, radius, radius);
}
