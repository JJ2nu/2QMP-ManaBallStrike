#include "pch.h"
#include "Collision.h"

bool Engine::Math::Collision::Collision::operator()(const Rect& collisionRect, const Rect& targetRect, Manifold* manifold) const
{
	bool overlapX = (collisionRect.left < targetRect.right) && (collisionRect.right > targetRect.left);
	bool overlapY = (collisionRect.top < targetRect.bottom) && (collisionRect.bottom > targetRect.top);

	if (overlapX && overlapY)
	{
		if (manifold)
		{
			float overlapLeft = targetRect.right - collisionRect.left;
			float overlapRight = collisionRect.right - targetRect.left;
			float overlapTop = targetRect.bottom - collisionRect.top;
			float overlapBottom = collisionRect.bottom - targetRect.top;


			if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom)
			{
				manifold->collisionNormal = { -1, 0 };
				manifold->overlapAmount = overlapLeft;
				manifold->collisionPoint = { collisionRect.left - overlapLeft, collisionRect.top };
			}
			else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom)
			{
				manifold->collisionNormal = { 1, 0 };
				manifold->overlapAmount = overlapRight;
				manifold->collisionPoint = { collisionRect.right + overlapRight, collisionRect.top };
			}
			else if (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight)
			{
				manifold->collisionNormal = { 0, -1 };
				manifold->overlapAmount = overlapTop;
				manifold->collisionPoint = { collisionRect.left, collisionRect.top - overlapTop };
			}
			else
			{
				manifold->collisionNormal = { 0, 1 };
				manifold->overlapAmount = overlapBottom;
				manifold->collisionPoint = { collisionRect.left, collisionRect.bottom + overlapBottom };
			}
		}
		return true;
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Rect& collisionRect, const Circle& targetCircle, Manifold* manifold) const
{
	Vector2 closest = { Helper::Max()(collisionRect.left, Helper::Min()(targetCircle.center.x, collisionRect.right)),
						Helper::Max()(collisionRect.top, Helper::Min()(targetCircle.center.y, collisionRect.bottom)) };

	Vector2 distance = targetCircle.center - closest;
	float distAmount = distance.Magnitude();

	if (distAmount <= targetCircle.radius + _epsilon)
	{
		if (manifold)
		{
			manifold->collisionNormal = distance.Normalize();
			manifold->overlapAmount = targetCircle.radius - distAmount;
			manifold->collisionPoint = targetCircle.center + manifold->collisionNormal * manifold->overlapAmount;
		}
		return true;
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Rect& collisionRect, const Vector2& targetPoint, Manifold* manifold) const
{
	if (targetPoint.x >= collisionRect.left && targetPoint.x <= collisionRect.right &&
		targetPoint.y >= collisionRect.top && targetPoint.y <= collisionRect.bottom)
	{
		if (manifold)
		{
			float distToLeft = targetPoint.x - collisionRect.left;
			float distToRight = collisionRect.right - targetPoint.x;
			float distToTop = targetPoint.y - collisionRect.top;
			float distToBottom = collisionRect.bottom - targetPoint.y;

			float minDist = Helper::Max()(Helper::Max()(distToLeft, distToRight), Helper::Max()(distToTop, distToBottom));

			if (minDist == distToLeft)
			{
				manifold->collisionNormal = { -1, 0 };
				manifold->overlapAmount = distToLeft;
				manifold->collisionPoint = { collisionRect.left - _epsilon, targetPoint.y };
			}
			else if (minDist == distToRight)
			{
				manifold->collisionNormal = { 1, 0 };
				manifold->overlapAmount = distToRight;
				manifold->collisionPoint = { collisionRect.right + _epsilon, targetPoint.y };
			}
			else if (minDist == distToTop)
			{
				manifold->collisionNormal = { 0, -1 };
				manifold->overlapAmount = distToTop;
				manifold->collisionPoint = { targetPoint.x, collisionRect.top - _epsilon };
			}
			else
			{
				manifold->collisionNormal = { 0, 1 };
				manifold->overlapAmount = distToBottom;
				manifold->collisionPoint = { targetPoint.x, collisionRect.bottom + _epsilon };
			}
		}
		return true;
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Rect& collisionRect, const RoundRect& targetRoundRect, Manifold* manifold) const
{
	if ((*this)(collisionRect, targetRoundRect.GetOuterRect(), manifold)) return true;

	Circle cornerCircles[4] = {
		{ targetRoundRect.rect.left + targetRoundRect.radiusX, targetRoundRect.rect.top + targetRoundRect.radiusY, targetRoundRect.radiusX },
		{ targetRoundRect.rect.right - targetRoundRect.radiusX, targetRoundRect.rect.top + targetRoundRect.radiusY, targetRoundRect.radiusX },
		{ targetRoundRect.rect.left + targetRoundRect.radiusX, targetRoundRect.rect.bottom - targetRoundRect.radiusY, targetRoundRect.radiusX },
		{ targetRoundRect.rect.right - targetRoundRect.radiusX, targetRoundRect.rect.bottom - targetRoundRect.radiusY, targetRoundRect.radiusX }
	};

	for (const auto& circle : cornerCircles)
	{
		if (operator()(collisionRect, circle, manifold)) return true;
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Circle& collisionCircle, const Circle& targetCircle, Manifold* manifold) const
{
	Vector2 distance = targetCircle.center - collisionCircle.center;
	float distAmount = distance.Magnitude();
	float radiusSum = targetCircle.radius + collisionCircle.radius;

	if (distAmount <= radiusSum + _epsilon)
	{
		if (manifold)
		{
			manifold->collisionNormal = distance.Normalize();
			manifold->overlapAmount = radiusSum - distAmount;
			manifold->collisionPoint = collisionCircle.center - manifold->collisionNormal * (collisionCircle.radius - manifold->overlapAmount);
		}
		return true;
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Circle& collisionCircle, const Rect& targetRect, Manifold* manifold) const
{
	return (*this)(targetRect, collisionCircle, manifold);
}

bool Engine::Math::Collision::Collision::operator()(const Circle& collisionCircle, const Vector2& targetPoint, Manifold* manifold) const
{
	Vector2 distance = targetPoint - collisionCircle.center;
	float distAmount = distance.Magnitude();

	if (distAmount < collisionCircle.radius)
	{
		if (manifold)
		{
			manifold->collisionNormal = distance.Normalize();
			manifold->overlapAmount = collisionCircle.radius - distAmount;
			manifold->collisionPoint = collisionCircle.center + manifold->collisionNormal * collisionCircle.radius;
		}
		return true;
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Circle& collisionCircle, const RoundRect& targetRoundRect, Manifold* manifold) const
{
	if ((*this)(targetRoundRect.GetOuterRect(), collisionCircle, manifold)) return true;

	Circle cornerCircles[4] = {
	   { targetRoundRect.rect.left + targetRoundRect.radiusX, targetRoundRect.rect.top + targetRoundRect.radiusY, targetRoundRect.radiusX },
	   { targetRoundRect.rect.right - targetRoundRect.radiusX, targetRoundRect.rect.top + targetRoundRect.radiusY, targetRoundRect.radiusX },
	   { targetRoundRect.rect.left + targetRoundRect.radiusX, targetRoundRect.rect.bottom - targetRoundRect.radiusY, targetRoundRect.radiusX },
	   { targetRoundRect.rect.right - targetRoundRect.radiusX, targetRoundRect.rect.bottom - targetRoundRect.radiusY, targetRoundRect.radiusX }
	};

	for (const auto& cornerCircle : cornerCircles)
	{
		Vector2 distance = collisionCircle.center - cornerCircle.center;
		float distAmount = distance.Magnitude();
		float radiusSum = collisionCircle.radius + cornerCircle.radius;

		if (distAmount <= radiusSum + _epsilon)
		{
			if (manifold)
			{
				manifold->collisionNormal = distance.Normalize();
				manifold->overlapAmount = radiusSum - distAmount;
				manifold->collisionPoint = collisionCircle.center - manifold->collisionNormal * collisionCircle.radius;
				manifold->overlapAmount = Helper::Min()(manifold->overlapAmount, collisionCircle.radius);
			}
			return true;
		}
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Vector2& collisionPoint, const Vector2& targetPoint, Manifold* manifold) const
{
	if (collisionPoint == targetPoint)
	{
		if (manifold)
		{
			manifold->collisionPoint = collisionPoint;
		}
		return true;
	}
	return false;
}

bool Engine::Math::Collision::Collision::operator()(const Vector2& collisionPoint, const Rect& targetRect, Manifold* manifold) const
{
	return (*this)(targetRect, collisionPoint, manifold);
}

bool Engine::Math::Collision::Collision::operator()(const Vector2& collisionPoint, const Circle& targetCircle, Manifold* manifold) const
{
	return (*this)(targetCircle, collisionPoint, manifold);
}

bool Engine::Math::Collision::Collision::operator()(const Vector2& collisionPoint, const RoundRect& targetRoundRect, Manifold* manifold) const
{
	return (*this)(targetRoundRect, collisionPoint, manifold);
}

bool Engine::Math::Collision::Collision::operator()(const RoundRect& collisionRoundRect, const Vector2& targetPoint, Manifold* manifold) const
{
	if ((*this)(collisionRoundRect.GetOuterRect(), targetPoint, manifold)) return true;

	Circle cornerCircles[4] = {
		{ collisionRoundRect.rect.left + collisionRoundRect.radiusX, collisionRoundRect.rect.top + collisionRoundRect.radiusY, collisionRoundRect.radiusX },
		{ collisionRoundRect.rect.right - collisionRoundRect.radiusX, collisionRoundRect.rect.top + collisionRoundRect.radiusY, collisionRoundRect.radiusX },
		{ collisionRoundRect.rect.left + collisionRoundRect.radiusX, collisionRoundRect.rect.bottom - collisionRoundRect.radiusY, collisionRoundRect.radiusX },
		{ collisionRoundRect.rect.right - collisionRoundRect.radiusX, collisionRoundRect.rect.bottom - collisionRoundRect.radiusY, collisionRoundRect.radiusX }
	};

	for (const auto& circle : cornerCircles)
	{
		if (operator()(circle, targetPoint, manifold)) return true;
	}

	return false;
}

bool Engine::Math::Collision::Collision::operator()(const RoundRect& collisionRoundRect, const Circle& targetCircle, Manifold* manifold) const
{
	return (*this)(targetCircle, collisionRoundRect, manifold);
}

bool Engine::Math::Collision::Collision::operator()(const RoundRect& collisionRoundRect, const Rect& targetRect, Manifold* manifold) const
{
	return (*this)(targetRect, collisionRoundRect, manifold);
}

bool Engine::Math::Collision::Collision::operator()(const RoundRect& collisionRoundRect, const RoundRect& targetRoundRect, Manifold* manifold) const
{
	if ((*this)(collisionRoundRect.GetOuterRect(), targetRoundRect.GetOuterRect(), manifold)) return true;

	Circle collisionCorners[4] = {
		{ collisionRoundRect.rect.left + collisionRoundRect.radiusX, collisionRoundRect.rect.top + collisionRoundRect.radiusY, collisionRoundRect.radiusX },
		{ collisionRoundRect.rect.right - collisionRoundRect.radiusX, collisionRoundRect.rect.top + collisionRoundRect.radiusY, collisionRoundRect.radiusX },
		{ collisionRoundRect.rect.left + collisionRoundRect.radiusX, collisionRoundRect.rect.bottom - collisionRoundRect.radiusY, collisionRoundRect.radiusX },
		{ collisionRoundRect.rect.right - collisionRoundRect.radiusX, collisionRoundRect.rect.bottom - collisionRoundRect.radiusY, collisionRoundRect.radiusX }
	};

	Circle targetCorners[4] = {
		{ targetRoundRect.rect.left + targetRoundRect.radiusX, targetRoundRect.rect.top + targetRoundRect.radiusY, targetRoundRect.radiusX },
		{ targetRoundRect.rect.right - targetRoundRect.radiusX, targetRoundRect.rect.top + targetRoundRect.radiusY, targetRoundRect.radiusX },
		{ targetRoundRect.rect.left + targetRoundRect.radiusX, targetRoundRect.rect.bottom - targetRoundRect.radiusY, targetRoundRect.radiusX },
		{ targetRoundRect.rect.right - targetRoundRect.radiusX, targetRoundRect.rect.bottom - targetRoundRect.radiusY, targetRoundRect.radiusX }
	};

	for (const auto& collisionCircle : collisionCorners)
	{
		for (const auto& targetCircle : targetCorners)
		{
			if (operator()(collisionCircle, targetCircle, manifold)) return true;
		}
	}

	for (const auto& collisionCircle : collisionCorners)
	{
		if ((*this)(targetRoundRect.GetOuterRect(), collisionCircle, manifold))	return true;
	}

	for (const auto& targetCircle : targetCorners)
	{
		if ((*this)(collisionRoundRect.GetOuterRect(), targetCircle, manifold)) return true;
	}

	return false;
}
