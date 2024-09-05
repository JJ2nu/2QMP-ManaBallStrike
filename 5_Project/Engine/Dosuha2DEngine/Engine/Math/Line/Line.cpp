#include "pch.h"
#include "Line.h"

Engine::Math::Line::Line()
	: start{0, 0}, end{0, 0}, thickness(0)
{
}

Engine::Math::Line::Line(const float startX, const float startY, const float endX, const float endY, const float thickness)
	: start{startX, startY}, end{endX, endY}, thickness(thickness)
{
}

Engine::Math::Line::Line(const Vector2& start, const Vector2& end, const float thickness)
	: start(start), end(end), thickness(thickness)
{
}

float Engine::Math::Line::GetLength() const
{
	return Vector2::Distance(start, end);
}

float Engine::Math::Line::GetSquareLength() const
{
	return (end - start).SquareMagnitude();
}

Engine::Math::Vector2 Engine::Math::Line::GetDirection() const
{
	return end - start;
}
