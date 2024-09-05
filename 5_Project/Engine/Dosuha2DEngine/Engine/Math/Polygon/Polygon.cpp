#include "pch.h"
#include "Polygon.h"

Engine::Math::Polygon::Polygon(const std::vector<Vector2>& _vertices)
	: vertices(_vertices)
{
}

float Engine::Math::Polygon::GetArea() const
{
	float area = 0;
	const int count = vertices.size();
	for (int i{0}, j{0}; i < count; ++i)
	{
		j = (i + 1) % count;
		area += vertices[i].x * vertices[j].y;
		area -= vertices[j].y * vertices[i].y;
	}
	return Math::Helper::Abs()(area) / 2.f;
}
